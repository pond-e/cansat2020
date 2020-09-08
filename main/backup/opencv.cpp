#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<string>
#include<cmath>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>

using namespace std;
int main(void) {
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

		Mat gray;
		Mat flame;
		int key = waitKey(50);
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
		cvtColor(img, gray, COLOR_BGR2HSV);
		inRange(gray, Scalar(a, b, c), Scalar(d, e, f), frame);
		erode(frame, frame, Mat(), Point(-1, -1), 3);
		dilate(frame, frame, Mat(), Point(-1, -1), 5); 	
		imshow("default",img);
		imshow("flame",flame);

	}

	destroyAllWindows();
	cout << "*---------Main Start---------*" << endl;



	cv::Mat box;
	cvtColor(img, test, COLOR_BGR2HSV);
	inRange(test, Scalar(a, b, c), Scalar(d, e, f), test);
	erode(test, test, Mat(), Point(-1, -1), 3);
	dilate(test, test, Mat(), Point(-1, -1), 5);


	//輪郭抽出+最大面積抽出
	vector<vector<Point> > contours;
	findContours(bin_img, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	double max_area=0;
	int max_area_contour=-1;
	for(int j=0;j<contours.size();j++){

		double area=contourArea(contours.at(j));
		if(max_area<area){

			max_area=area;	
			max_area_contour=j;
		}
	}


	// 最大面積を持つ輪郭の最小外接円を取得
	cv::minEnclosingCircle(contours.at(max_area_contour), center, radius);
	printf("%f\n",&canter);


	//半径で縮尺を求める
	double R = 1/*パラシュート半径*//center;


	//ラべリング
	Mat LabelImg;
	Mat stats;
	Mat centroids;
	int nLab = connectedComponentsWithStats(maindst, LabelImg, stats, centroids);


	// 描画色決定
	vector<Vec3b> colors(nLab);
	colors[0] = Vec3b(0, 0, 0);
	for (int i = 1; i < nLab; ++i){

		colors[i] = Vec3b((rand() & 255), (rand() & 255), (rand() & 255)); 
	}


	//描画
	Mat Dst;
	for (int i = 0; i < Dst.rows; ++i){

		int *lb = LabelImg.ptr<int>(i);
		Vec3b *pix = Dst.ptr<Vec3b>(i);
		for (int j = 0; j < Dst.cols; ++j){

			pix[j] = colors[lb[j]];
		}
	}


	//重心計算
	double sample_area = max_area*0.4;
	int sample_area2 = sample_area
		int centerX[nLab] = {};
	int centerY[nLab] = {};
	int data =0;
	for (int i = 1; i < nLab; ++i){

		double *param = centroids.ptr<double>(i);
		if(param[ConnectedComponentsTypes::CC_STAT_AREA] >= sample_area){

			centerX[data] = static_cast<int>(param[0]);
			centerY[data] = static_cast<int>(param[1]);
			circle(Dst, Point(centerX[i], centerY[i]), 3, Scalar(0, 0, 255), -1);
			data =data+1;
		}
	}

	// ROIの設定

	int q=0;
	for (int i = 1; i < nLab; ++i){

		int *param = stats.ptr<int>(i);
		if(param[ConnectedComponentsTypes::CC_STAT_AREA] >= sample_area2){

			q=q+1;
			int x = param[ConnectedComponentsTypes::CC_STAT_LEFT];
			int y = param[ConnectedComponentsTypes::CC_STAT_TOP];
			int height = param[ConnectedComponentsTypes::CC_STAT_HEIGHT];
			int width = param[ConnectedComponentsTypes::CC_STAT_WIDTH];
			rectangle(Dst, Rect(x, y, width, height), Scalar(0, 255, 0), 2);
			stringstream num;
			num << q;
			putText(Dst, num.str(),Point(tableX+5, tableY+20), FONT_HERSHEY_COMPLEX,0.7, Scalar(0, 255, 255), 2);	
		}
	}

	cv::imwrite("Dst.png",Dst);//ROIの画像
	if(q=3){

		//面積を求める
		double D = fabs(1/2*(centerX[0]*centerY[1]+centerX[1]*centerY[2]+centerX[2]*centerY[0]-centerX[1]*centerY[0]-centerX[2]*centerY[1]-centerX[0]*centerY[2]));
		//縮尺をもとに算出	
		double AREA =D*R*R;
		printf("最終面積は%fm^2",&AREA);
	}else{

		cout <<"too more lab!!"<< endl;
	}		



	fstream fs;

	fs.open("output.txt", ios::out);
	if(! fs.is_open()) {
		return EXIT_FAILURE;
	}

	fs << "番号　重心位置[X, Y]" << endl;
       	fs << "1" << centerX[0] <<", " << centerY[0] << endl;
	fs << "2" << centerX[1] <<", " << centerY[1] << endl;
	fs << "3" << centerX[2] <<", " << centerY[2] << endl;
       
	fs << "縮尺[実寸/画像内]" << endl;
	fs << R << endl;

	fs << "面積[m^2]" << endl;
	fs << AREA << endl;

	// 改行。そして書き出す
	// close() で暗黙的に書き出す (閉じるときにバッファをすべて書き出してくれる)
	fs.close();

	return 0;
}







return 0;

}
