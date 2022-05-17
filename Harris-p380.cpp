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

	Mat cornerStrength;
	cornerHarris(src,cornerStrength,2,3,0.01);

	Mat harrisCorner;
	threshold(cornerStrength,harrisCorner,0.00001,255,THRESH_BINARY);

	namedWindow("output",CV_WINDOW_AUTOSIZE);
	imshow("output", harrisCorner);
	

	waitKey(0);
	return 0;
}