#include<iostream>
#include<vector>
#include<random>
#include<string>
#include<stdlib.h>
#include<fstream>
#include<cmath>
#include<opencv2/opencv.hpp>
#include<opencv2/imgproc/types_c.h>
using namespace std;

int main(void) {
	int a=0;
	int b=0;
       	int c=0;
       	int d=255;
       	int e=255;
	int f=255;

	cv::Mat img;
	cv::Mat test;

	//filename入力
	img = cv::imread("1.png");
	if (img.empty()) {
		// 画像の中身が空なら終了する
		cout << "not available" <<endl;
		exit(1);	
	}


	while(true){

		cv::Mat gray;
		cv::Mat frame;
		int key = cv::waitKey(50);
		bool swflag = false;

		switch (key){//二値化

			case 113://Q
				a = a + 5;
				break;
			case 97://A
				a = a - 3;
				break;
			case 119://W
				b = b + 5;
				break;
			case 115://S
				b = b - 3;
				break;
			case 101://E
				c = c + 5;
				break;//D
			case 100:
				c = c - 3;
				break;
			case 116://T
				d = d - 5;
				break;
			case 103://G
				d = d + 3;
				break;
			case 121://Y
				e = e - 5;
				break;
			case 104://H
				e = e + 3;
				break;
			case 117://U
				f = f - 5;
				break;
			case 106://J
				f = f + 3;
				break;
			case 32://spaceで撮影
				swflag = true;
				break;
		}

		if (swflag == true){

			//imwrite("range.png",flame);//二値化画像保存
			break;
		}


		printf("(%d,%d,%d)\n", a, b, c);
		printf("(%d,%d,%d)\n", d, e, f);
		cv::cvtColor(img, gray, cv::COLOR_BGR2HSV);
		cv::inRange(gray, cv::Scalar(a, b, c), cv::Scalar(d, e, f), frame);
		cv::erode(frame, frame, cv::Mat(), cv::Point(-1, -1), 3);
		cv::dilate(frame, frame, cv::Mat(), cv::Point(-1, -1), 5); 	
		cv::imshow("default",img);
		cv::imshow("frame",frame);

	}

	cv::destroyAllWindows();
	cout << "*---------Main Start---------*" << endl;



	cv::Mat box;
	cv::cvtColor(img, test, cv::COLOR_BGR2HSV);
	cv::inRange(test, cv::Scalar(a, b, c), cv::Scalar(d, e, f), test);
	cv::erode(test, test, cv::Mat(), cv::Point(-1, -1), 3);
	cv::dilate(test, test, cv::Mat(), cv::Point(-1, -1), 5);


	//輪郭抽出+最大面積抽出
	cv::Point2f center;
      	float radius;
	std::vector<std::vector<cv::Point>> contours;
	cv::findContours(test, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	double max_area=0;
	int max_area_contour=-1;
	for(int j=0;j<contours.size();j++){

		double area=cv::contourArea(contours.at(j));
		if(max_area<area){

			max_area=area;	
			max_area_contour=j;
		}
	}

/*
    void imageCb(const sensor_msgs::ImageConstPtr& msg){
      cv::Point2f center, p1;
      float radius;

      cv_bridge::CvImagePtr cv_ptr, cv_ptr2, cv_ptr3;
   */
	// 最大面積を持つ輪郭の最小外接円を取得
	cv::minEnclosingCircle(contours.at(max_area_contour), center, radius);
	printf("%lf\n",radius);


	//半径で縮尺を求める
	double R = 0.145/radius;


	//ラべリング
	cv::Mat LabelImg;
	cv::Mat stats;
	cv::Mat centroids;
	int nLab = cv::connectedComponentsWithStats(test, LabelImg, stats, centroids);


	// 描画色決定
	vector<cv::Vec3b> colors(nLab);
	colors[0] = cv::Vec3b(0, 0, 0);
	for (int i = 1; i < nLab; ++i){

		colors[i] = cv::Vec3b((rand() & 255), (rand() & 255), (rand() & 255)); 
	}


	//描画
	cv::Mat Dst(test.size(), CV_8UC3);;
	for (int i = 0; i < Dst.rows; ++i){

		int *lb = LabelImg.ptr<int>(i);
		cv::Vec3b *pix = Dst.ptr<cv::Vec3b>(i);
		for (int j = 0; j < Dst.cols; ++j){

			pix[j] = colors[lb[j]];
		}
	}


	//重心計算
	double sample_area = max_area*0.4;
	int sample_area2 = sample_area;
	int centerX[nLab];
	int centerY[nLab];
	int data =0;
	for (int i = 1; i < nLab; ++i){

		double *param = centroids.ptr<double>(i);
		centerX[i] = static_cast<int>(param[0]);
		centerY[i] = static_cast<int>(param[1]);
		cv::circle(Dst, cv::Point(centerX[i], centerY[i]), 3, cv::Scalar(0, 0, 255), -1);
	}


	// ROIの設定
	int q=0;
	int LastcenterX[nLab] = {};
	int LastcenterY[nLab] = {};
	for (int i = 1; i < nLab; ++i){

		int *param = stats.ptr<int>(i);
		if(param[cv::ConnectedComponentsTypes::CC_STAT_AREA] >= sample_area2){

			int x = param[cv::ConnectedComponentsTypes::CC_STAT_LEFT];
			int y = param[cv::ConnectedComponentsTypes::CC_STAT_TOP];
			int height = param[cv::ConnectedComponentsTypes::CC_STAT_HEIGHT];
			int width = param[cv::ConnectedComponentsTypes::CC_STAT_WIDTH];
			cv::rectangle(Dst, cv::Rect(x, y, width, height), cv::Scalar(0, 255, 0), 2);
			stringstream num;
			num << q;
			cv::putText(Dst, num.str(),cv::Point(x+5, y+20), cv::FONT_HERSHEY_COMPLEX,0.7, cv::Scalar(0, 255, 255), 2);	
			LastcenterX[q] = centerX[i];
			LastcenterY[q] = centerY[i];
			q = q+1;
		}
	}

	cv::imwrite("Dst.png",Dst);//ROIの画像
	double D,E;
	double Are,Are2;
	if(q=3){

		//面積を求める
		double s1 = LastcenterX[0]*LastcenterY[1];
		double s2 = LastcenterX[1]*LastcenterY[2];
		double s3 = LastcenterX[2]*LastcenterY[0];
		double s4 = LastcenterX[1]*LastcenterY[0];
		double s5 = LastcenterX[2]*LastcenterY[1];
		double s6 = LastcenterX[0]*LastcenterY[2];
		D = fabs((s1+s2+s3-s4-s5-s6)/2);

		fstream fs;

	        fs.open("output3.txt", ios::out);
        	if(! fs.is_open()) {
                	return EXIT_FAILURE;
        	}

        	fs << "番号　重心位置[X, Y]" << endl;
        	fs << "1" << "," << LastcenterX[0] <<", " << LastcenterY[0] << endl;
        	fs << "2" << "," << LastcenterX[1] <<", " << LastcenterY[1] << endl;
        	fs << "3" << "," << LastcenterX[2] <<", " << LastcenterY[2] << endl;

        	fs << "縮尺[実寸/画像内]" << endl;
        	fs << R << endl;
	
        	fs << "面積[m^2]" << endl;
        	fs <<  Are << endl;
	
        	// 改行。そして書き出す
        	// close() で暗黙的に書き出す (閉じるときにバッファをすべて書き出してくれる)
        	fs.close();


		//縮尺をもとに算出	
		Are =D*R*R;
		printf("are=%f\n",D);
		printf("最終面積は%fm^2\n",Are);
	}else if(q=4){

	
		//面積を求める
                double m1 = LastcenterX[0]*(LastcenterY[3]-LastcenterY[1]);
                double m2 = LastcenterX[1]*(LastcenterY[0]-LastcenterY[2]);
                double m3 = LastcenterX[2]*(LastcenterY[1]-LastcenterY[3]);
                double m4 = LastcenterX[3]*(LastcenterY[2]-LastcenterY[0]);
             
                E = fabs((m1+m2+m3+m4)/2);

                fstream fs;

                fs.open("output4.txt", ios::out);
                if(! fs.is_open()) {
                        return EXIT_FAILURE;
                }

                fs << "番号　重心位置[X, Y]" << endl;
                fs << "1" << "," << LastcenterX[0] <<", " << LastcenterY[0] << endl;
                fs << "2" << "," << LastcenterX[1] <<", " << LastcenterY[1] << endl;
                fs << "3" << "," << LastcenterX[2] <<", " << LastcenterY[2] << endl;
		fs << "4" << "," << LastcenterX[3] <<", " << LastcenterY[3] << endl;

                fs << "縮尺[実寸/画像内]" << endl;
                fs << E << endl;

                fs << "面積[m^2]" << endl;
                fs <<  Are2 << endl;

                // 改行。そして書き出す
                // close() で暗黙的に書き出す (閉じるときにバッファをすべて書き出してくれる)
                fs.close();


                //縮尺をもとに算出      
                Are =E*R*R;
                printf("are=%f\n",E);
                printf("最終面積は%fm^2\n",Are2);

	
	
	}else{

		cout <<"too more lab!!"<< endl;
	}		



	return 0;
}

