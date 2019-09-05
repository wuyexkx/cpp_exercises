#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
using namespace cv;
using namespace std;
 
// int main()
// {
// 	VideoCapture cap;
// 	cap = VideoCapture(CV_CAP_DSHOW);	//使用DirectShow
// 	cap.open(1);						//这是我的USB摄像头
// 	if (!cap.isOpened())
// 		return -1;
// 	cap.set(CV_CAP_PROP_FOURCC, CV_FOURCC('M', 'J', 'P', 'G'));//设置为MJPG格式
// 	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 640);
// 	cap.set(CV_CAP_PROP_FRAME_WIDTH, 480);
// 	TickMeter tm;
 
// 	while (1)
// 	{
 
// 		tm.reset();
// 		tm.start();
// 		Mat frame;
// 		for (int i = 0; i < 100; i++)//Is not accuracy when I count once.
// 		{
// 			cap >> frame;
// 			// imshow("frame", frame);
// 			if(waitKey(1)==27) return 0;//ESC for quit
// 		}
// 		tm.stop();
// 		cout << 100 / tm.getTimeSec() << "fps" << endl;//输出帧率
// 	}
// 	return 0;
// }


//  读取视频
int main()
{
    VideoCapture capture;
    Mat frame;
    frame= capture.open("C:/Users/wyxkx/Desktop/1.avi");
    if(!capture.isOpened())
    {
        printf("can not open ...\n");
        return -1;
    }

    TickMeter tm;
    tm.reset();
    tm.start();

    while (capture.read(frame))
    {
		for (int i = 0; i < 100; i++)//Is not accuracy when I count once.
		{
			capture >> frame;
			imshow("frame", frame);
			if(waitKey(1)==27) return 0;//ESC for quit
		}
		tm.stop();
		cout << 100 / tm.getTimeSec() << "fps" << endl;//输出帧率
	}
    capture.release();
    return 0;
}
