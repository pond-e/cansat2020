#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include<time.h>

//#include<thread>



using namespace std;
int main(){
    	clock_t start;
	clock_t end;

	time_t a_t;
	time_t b_t;
	time_t c_t;

	a_t =time(NULL);



	cv::VideoCapture cap(0);
        if (!cap.isOpened()) {
                cout << "Not Opened" << endl;
                return -1;
        } else {
                cout << "Open Successful" << endl;
        }

	std::string filepath = "output.mp4";
	cv::Mat frame;
	cv::Mat img;
	//Mat out; //フレーム格納用
	
	int fourcc = cv::VideoWriter::fourcc('M','P','4','V');
	
	double fps = cap.get(cv::CAP_PROP_FPS); //動画からfpsを取得
	
	int width = cap.get(cv::CAP_PROP_FRAME_WIDTH); //動画から幅を取得
	int height = cap.get(cv::CAP_PROP_FRAME_HEIGHT); //動画から高さを取得
	
	cv::VideoWriter out("output.mp4", fourcc, 60, cv::Size(width, height),1); //出力用のオブジェクト
	while(true){
		b_t = time(NULL);
		c_t = b_t-a_t;
                if(c_t>10){i//着地後終了
	 		break;           
		}		
		start = clock();
		cap >> img;	
		out << img;
		end = clock();
		double t = end-start;
		double s  =1000000/fps - t;
		int s2 = s;
		//printf("%f",fps);
		//printf("%f,%d\n",s,s2);
		usleep(s2);

	}
	cv::VideoCapture release();
	cv::destroyAllWindows();

	//サーボでパラシュート切り離し
	


    return 0;
}
