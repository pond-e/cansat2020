/*　 動画から連番画像を出力　*/

//#include "pch.h"
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
    Mat img;

    //動画をキャプチャ
    VideoCapture cap("pi5.avi"); //Windowsの場合　パス中の¥は重ねて¥¥とする
    //VideoCapture cap("videos/sample.mp4"); //Macの場合

    //動画の最大フレーム数
    int max_frame = (int)cap.get(CAP_PROP_FRAME_COUNT);
    // 動画の高さ
    int img_h = (int)cap.get(CAP_PROP_FRAME_HEIGHT);
    // 動画の幅
    int img_w = (int)cap.get(CAP_PROP_FRAME_HEIGHT);
    // 動画のfps
    double fps = cap.get(CAP_PROP_FPS);

    for (int i = 0; i < max_frame; i++) {

        //1フレーム分取り出してimgに保持させる
        cap >> img;

        //現在のフレーム番号を表示
        std::cout << "フレーム番号 " << i << std::endl;

        //画像を表示
        imshow("Video", img);

        //取得した画像を連番画像で保存
        std::ostringstream oss;
        oss << std::setfill('0') << std::setw(3) << i;
        cv::imwrite("pic/movie_img" + oss.str() + ".png", img);

        // 表示のために30ms待つ
        waitKey(30);
    }
    //動画情報の出力
    std::cout << "フレーム番号 " << max_frame - 1 << std::endl;//345
    std::cout << "動画の高さ " << img_h << std::endl; //352
    std::cout << "動画の幅 " << img_w << std::endl;// 352
    std::cout << "動画のfps " << fps << std::endl;// 15return 0;

}

/*
C:\opencv\build\include
C:\opencv\build\x64\vc15\lib
opencv_world400.lib;%(AdditionalDependencies)
*/
