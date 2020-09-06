#include <iostream> 
#include "opencv2/highgui.hpp"
//#include "opencv2/Videoio.hpp"
#include <opencv2/core.hpp>
using namespace cv;
using namespace std;
int main(){
    
	VideoCapture cap(0);
        if (!cap.isOpened()) {
                cout << "Not Opened" << endl;
                return -1;
        } else {
                cout << "Open Successful" << endl;
        }

	 std::string filepath = "output.mp4";
	Mat frame;
	Mat img;
	//Mat out; //フレーム格納用
	
	int fourcc = cv::VideoWriter::fourcc('x','V','I','D');
	
	double fps = cap.get(cv::CAP_PROP_FPS); //動画からfpsを取得
	
	int width = cap.get(cv::CAP_PROP_FRAME_WIDTH); //動画から幅を取得
	int height = cap.get(cv::CAP_PROP_FRAME_HEIGHT); //動画から高さを取得
	
	VideoWriter out("output.avi", fourcc, fps, cv::Size(width, height)); //出力用のオブジェクト

	//while(1){
	for(int i=0;i<=30;i++){
		cap >> img;
		out << img;
	
	int key = cv::waitKey(1);
		if(key == 'q'){
			
			cv::destroyAllWindows();
			cap.release();
			break; //whileループから抜ける
		}
	
	
	
	}




	/*VideoCapture cap(0);
        if (!cap.isOpened()) {
                cout << "Not Opened" << endl;
                return -1;
        } else {
                cout << "Open Successful" << endl;
        }
	int max_frame=cap.get(CV_CAP_PROP_FRAME_COUNT);
	int CV_FOURCC_MACRO('M','P','4','V')
        VideoWriter writer("a.mp4", CV_FOURCC_MACRO('M','P','4','V'), 30, cv::Size(600, 600), true);


	
	Mat img;
	VideoCapture cap("sample.mp4");
    	int max_frame=cap.get(CV_CAP_PROP_FRAME_COUNT);
    	VideoWriter writer("output.avi", CV_FOURCC_DEFAULT, 30, cv::Size(600, 600), true);
    	for(int i=0; i<max_frame;i++){
        cap>>img ;
        writer << img;
        imshow("Video",img);
        waitKey(1);

	*/
    
    return 0;
}
