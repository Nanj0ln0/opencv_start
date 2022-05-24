#include <opencv2/opencv.hpp>
#include <iostream>
#include <opencv2/xfeatures2d.hpp>

using namespace cv;
using namespace std;
using namespace cv::xfeatures2d;

int main() {

	Mat src = imread("C:/Users/22207/Desktop/superis/jianzhuwu.JPG");
	if (!src.data)
	{
		printf("ERRPR");
		return -1;
	}
	namedWindow("input",CV_WINDOW_AUTOSIZE);
	imshow("input",src);

	//参数定义
	int numFeatures = 100;
	Ptr<SIFT> detector = SIFT::create(numFeatures);

	vector<KeyPoint>KeyPoints;
	detector->detect(src,KeyPoints,Mat());

	printf("共有特征点%d个\n",KeyPoints.size());

	Mat keyPoint_img = src.clone();
	drawKeypoints(src,KeyPoints,keyPoint_img,Scalar::all(-1),DrawMatchesFlags::DEFAULT);

	namedWindow("sift", CV_WINDOW_AUTOSIZE);
	imshow("sift",keyPoint_img);

	waitKey(0);
	return 0;
}