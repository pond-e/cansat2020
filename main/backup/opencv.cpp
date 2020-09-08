#include<iostream>
#include<stdlib.h>
#include<string>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>

using namespace std;
int main(void) {
	cv::Mat img;
	//filename入力
	
	img = cv::imread("filename");
	if (img.empty()) {
		// 画像の中身が空なら終了する
		cout << "できませんでした" <<endl;
		exit(1);	
	}


	while(true){

	return 0;
}
/*


		//画像撮影
		cv::Mat img, dst;
                cap >> img;
		imwrite("img.png", img);
		cvtColor(img, dst, cv::COLOR_BGR2GRAY);
                
		//1
		Scalar s_min = Scalar(B_MIN, G_MIN, R_MIN);
                Scalar s_max = Scalar(B_MAX, G_MAX, R_MAX);
                inRange(input_image_rgb, s_min, s_max, mask_image);
	       	//2
		Scalar s_min = Scalar(B_MIN, G_MIN, R_MIN);
                Scalar s_max = Scalar(B_MAX, G_MAX, R_MAX);
                inRange(input_image_rgb, s_min, s_max, mask_image);
		//3
		Scalar s_min = Scalar(B_MIN, G_MIN, R_MIN);
		Scalar s_max = Scalar(B_MAX, G_MAX, R_MAX);
		inRange(input_image_rgb, s_min, s_max, mask_image);


                erode(frame, frame, Mat(), Point(-1, -1), 3);
                dilate(frame, frame, Mat(), Point(-1, -1), 5);
                imshow("binary img", frame);
                waitKey(200);
cap >> mainframe;
                Mat maindst(mainframe, Rect(X_ORIGIN, Y_ORIGIN, X_SIZE, Y_SIZE));
                resize(maindst, maindst, Size(X_SIZE, Y_SIZE));
                cvtColor(maindst, mainhsv, COLOR_BGR2HSV);
                inRange(mainhsv, Scalar(a, b, c), Scalar(d, e, f), maindst);
                erode(maindst, maindst, Mat(), Point(-1, -1), 3);
                dilate(maindst, maindst, Mat(), Point(-1, -1), 5);
                imwrite("img.jpg", maindst);




	cv::Mat color = cv::imread("hoge.png", 1);   // Read as Color image
	cv::Mat gray;
	cv::cvtColor(color, gray, cv::COLOR_BGR2GRAY);

	*/
