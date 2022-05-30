#include <opencv2/opencv.hpp>
#include <iostream>
#include <opencv2/xfeatures2d.hpp>
#include <math.h>

using namespace cv;
using namespace std;
using namespace cv::xfeatures2d;


int main() {
	Mat src1 = imread("C:/Users/22207/Desktop/superis/pipei0.JPG", 0);
	Mat src2 = imread("C:/Users/22207/Desktop/superis/pipei0 - 1.JPG", 0);
	if (!src1.data || !src2.data)
	{
		printf("ERROR");
		return -1;
	}

	namedWindow("input1", CV_WINDOW_AUTOSIZE);
	namedWindow("input2", CV_WINDOW_AUTOSIZE);
	imshow("input1", src1);
	imshow("input2", src2);


	waitKey(0);
	return 0;
}

