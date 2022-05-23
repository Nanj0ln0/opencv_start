#include <opencv2/opencv.hpp>
#include <iostream>
#include <opencv2/xfeatures2d.hpp>

using namespace cv;
using namespace std;
using namespace cv::xfeatures2d;

Mat src, src_gray;

const char* input_title = "inputPicture";

int main() {
	src = imread("C:/Users/22207/Desktop/superis/jianzhuwu.JPG");
	if (!src.data)
	{
		printf("ERROR");
		return -1;
	}
	namedWindow(input_title,CV_WINDOW_AUTOSIZE);
	namedWindow("outpoint", CV_WINDOW_AUTOSIZE);
	cvtColor(src,src_gray,COLOR_BGR2GRAY);
	imshow(input_title,src);

	//参数准备
	int minHessian = 400;
	Ptr<SURF>detector = SURF::create(minHessian);
	vector<KeyPoint>KeyPoints;
	
	detector->detect(src,KeyPoints,Mat());

	Mat keypoint_img;

	drawKeypoints(src,KeyPoints,keypoint_img,Scalar::all(-1),DrawMatchesFlags::DEFAULT);

	imshow("outpoint",keypoint_img);


	waitKey(0);
	return 0;

}