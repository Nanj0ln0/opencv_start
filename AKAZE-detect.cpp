#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
	Mat src = imread("C:/Users/22207/Desktop/superis/jianzhuwu.JPG",0);
	if (!src.data)
	{
		printf("ERROR");
		return -1;
	}
	namedWindow("input",CV_WINDOW_AUTOSIZE);
	imshow("input",src);


	//kaze detection
	Ptr<AKAZE>detector = AKAZE::create();
	vector<KeyPoint>KeyPoints;
	detector->detect(src,KeyPoints,Mat());

	Mat keypointImg;
	namedWindow("keypointImg",CV_WINDOW_AUTOSIZE);
	drawKeypoints(src,KeyPoints,keypointImg,Scalar::all(-1),DrawMatchesFlags::DEFAULT);
	imshow("keypointImg",keypointImg);

	waitKey(0);
	return 0;

}