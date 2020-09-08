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
	int a, b, c, d, e, f;

	cv::Mat img;
	cv::Mat test;

	//filename入力
	img = cv::imread("filename");
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
	double R = 1/*パラシュート半径*//radius;


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
	cv::Mat Dst;
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
	int centerX[nLab] = {};
	int centerY[nLab] = {};
	int data =0;
	for (int i = 1; i < nLab; ++i){

		double *param = centroids.ptr<double>(i);
		if(param[cv::ConnectedComponentsTypes::CC_STAT_AREA] >= sample_area){

			centerX[data] = static_cast<int>(param[0]);
			centerY[data] = static_cast<int>(param[1]);
			cv::circle(Dst, cv::Point(centerX[i], centerY[i]), 3, cv::Scalar(0, 0, 255), -1);
			data =data+1;
		}
	}


	// ROIの設定
	int q=0;
	for (int i = 1; i < nLab; ++i){

		int *param = stats.ptr<int>(i);
		if(param[cv::ConnectedComponentsTypes::CC_STAT_AREA] >= sample_area2){

			q=q+1;
			int x = param[cv::ConnectedComponentsTypes::CC_STAT_LEFT];
			int y = param[cv::ConnectedComponentsTypes::CC_STAT_TOP];
			int height = param[cv::ConnectedComponentsTypes::CC_STAT_HEIGHT];
			int width = param[cv::ConnectedComponentsTypes::CC_STAT_WIDTH];
			cv::rectangle(Dst, cv::Rect(x, y, width, height), cv::Scalar(0, 255, 0), 2);
			stringstream num;
			num << q;
			cv::putText(Dst, num.str(),cv::Point(x+5, y+20), cv::FONT_HERSHEY_COMPLEX,0.7, cv::Scalar(0, 255, 255), 2);	
		}
	}

	cv::imwrite("Dst.png",Dst);//ROIの画像
	if(q=3){

		//面積を求める
		double D = abs(1/2*(centerX[0]*centerY[1]+centerX[1]*centerY[2]+centerX[2]*centerY[0]-centerX[1]*centerY[0]-centerX[2]*centerY[1]-centerX[0]*centerY[2]));
		//縮尺をもとに算出	
		double A =D*R*R;
		printf("最終面積は%fm^2",A);
	}else{

		cout <<"too more lab!!"<< endl;
	}		



	fstream fs;

	fs.open("output.txt", ios::out);
	if(! fs.is_open()) {
		return EXIT_FAILURE;
	}

	fs << "番号　重心位置[X, Y]" << endl;
       	fs << "1" << "centerX[0]:" <<", " << "centerY[0]:" << endl;
	fs << "2" << "centerX[1]:" <<", " << "centerY[1]:" << endl;
	fs << "3" << "centerX[2]:" <<", " << "centerY[2]:" << endl;
       
	fs << "縮尺[実寸/画像内]" << endl;
	fs << "R:" << endl;

	fs << "面積[m^2]" << endl;
	fs << "A:" << endl;

	// 改行。そして書き出す
	// close() で暗黙的に書き出す (閉じるときにバッファをすべて書き出してくれる)
	fs.close();

	return 0;
}

