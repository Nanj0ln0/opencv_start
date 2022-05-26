#include <opencv2/opencv.hpp>
#include <iostream>
#include <opencv2/xfeatures2d.hpp>
#include <math.h>

using namespace cv;
using namespace std;
using namespace cv::xfeatures2d;

const char* input = "input_picture";
const char* output = "ELPB_out";

int minR=3;
int maxR=20;
void ELPB_demo(int,void*);

Mat src;
Mat src_gray;
Mat elbpImg;

int main() {
	src = imread("C:/Users/22207/Desktop/superis/jianzhuwu.JPG");
	if (!src.data)
	{
		printf("ERROR");
		return -1;
	}
	namedWindow(input, CV_WINDOW_AUTOSIZE);
	imshow(input, src);
	//转灰度
	cvtColor(src, src_gray, COLOR_BGR2GRAY);

	namedWindow(output,CV_WINDOW_AUTOSIZE);
	createTrackbar("尺度半径范围：", output,&minR,maxR,ELPB_demo);
	ELPB_demo(0, 0);

	waitKey(0);
	return 0;
}

void ELPB_demo(int, void*) {

	int offset = minR * 2;
	elbpImg = Mat::zeros(src_gray.rows-offset,src_gray.cols - offset,CV_8UC1);
	int width = src_gray.cols;
	int height = src_gray.rows;

	int numNeightbors = 8;
	for (int n = 0; n < numNeightbors; n++)
	{
		//算出第一个点的位置
		float x = static_cast<float>(minR * 2) * cos(2 * CV_PI * n / static_cast<float>(numNeightbors));
		float y = static_cast<float>(minR * 2) * sin(2 * CV_PI * n / static_cast<float>(numNeightbors))

	}

}