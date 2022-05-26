#include <opencv2/opencv.hpp>
#include <iostream>
#include <opencv2/xfeatures2d.hpp>

using namespace cv;
using namespace std;
using namespace cv::xfeatures2d;
const char* input = "input_picture";

int	main() {
	Mat src = imread("C:/Users/22207/Desktop/superis/mans-2.jpg");
	if (!src.data)
	{
		printf("ERROR");
		return -1;
	}
	namedWindow(input, CV_WINDOW_AUTOSIZE);
	imshow(input,src);

	waitKey(0);
	return 0;
}