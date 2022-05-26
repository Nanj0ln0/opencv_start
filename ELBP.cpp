#include <opencv2/opencv.hpp>
#include <iostream>
#include <opencv2/xfeatures2d.hpp>

using namespace cv;
using namespace std;
using namespace cv::xfeatures2d;

const char* input = "input_picture";
const char* output = "ELPB_out";

int minR=3;
int maxR=20;
void ELPB_demo(int,void*);

int main() {
	Mat src = imread("C:/Users/22207/Desktop/superis/jianzhuwu.JPG");
	if (!src.data)
	{
		printf("ERROR");
		return -1;
	}
	namedWindow(input, CV_WINDOW_AUTOSIZE);
	imshow(input, src);
	//×ª»Ò¶È
	Mat src_gray;
	cvtColor(src, src_gray, COLOR_BGR2GRAY);

	namedWindow(output,CV_WINDOW_AUTOSIZE);
	createTrackbar("³ß¶È°ë¾¶·¶Î§£º", output,&minR,maxR,ELPB_demo);
	ELPB_demo(0, 0);

	waitKey(0);
	return 0;
}

void ELPB_demo(int, void*) {




}