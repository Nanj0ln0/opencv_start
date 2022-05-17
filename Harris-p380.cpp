#include<opencv2/opencv.hpp>
#include<iostream>

using namespace cv;

int main() {

	Mat src = imread("C:\\Users\\22207\\Desktop\\superis\\text.JPG",0);
	if (!src.data)
	{
		printf("ERROR");
		return -1;
	}
	namedWindow("imshow",CV_WINDOW_AUTOSIZE);
	imshow("imshow",src);



	waitKey(0);
	return 0;
}