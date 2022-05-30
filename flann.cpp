#include <opencv2/opencv.hpp>
#include <iostream>
#include <opencv2/xfeatures2d.hpp>

using namespace cv;
using namespace std;
using namespace cv::xfeatures2d;


int main() {
	Mat src1 = imread("C:/Users/22207/Desktop/superis/pipei0.JPG", 0);
	Mat src2 = imread("C:/Users/22207/Desktop/superis/pipei1.JPG", 0);
	if (!src1.data || !src2.data)
	{
		printf("ERROR");
		return -1;
	}

	namedWindow("input1", CV_WINDOW_AUTOSIZE);
	namedWindow("input2", CV_WINDOW_AUTOSIZE);
	namedWindow("pipei", CV_WINDOW_AUTOSIZE);
	imshow("input1", src1);
	imshow("input2", src2);

	//计算得到描述子
	int minHessian = 400;
	Ptr<SURF>detector = SURF::create(minHessian);
	vector<KeyPoint> ketPoint1;
	vector<KeyPoint> ketPoint2;
	Mat descritor1, descritor2;
	detector->detectAndCompute(src1,Mat(),ketPoint1,descritor1);
	detector->detectAndCompute(src2,Mat(),ketPoint2,descritor2);

	//match  flann匹配
	FlannBasedMatcher matcher;
	vector<DMatch> matches;
	matcher.match(descritor1,descritor2,matches);

	//find good match寻找好的描述子
	double mindist = 1000;
	double maxdist = 0;
	for (int i = 0; i < descritor1.rows; i++)
	{
		double dist = matches[i].distance;
		if (dist>maxdist)
		{
			maxdist = dist;
		}
		if (dist<mindist)
		{
			mindist = dist;
		}

	}
	printf("最大距离为：%f，最小距离为：%f\n",maxdist,mindist);

	vector<DMatch> goodmatches;
	for (int i = 0; i < descritor2.rows; i++)
	{
		double dist = matches[i].distance;
		if (dist < max(2*mindist,0.02))
		{
			goodmatches.push_back(matches[i]);
		}
	}

	Mat matchImg;
	drawMatches(src1,ketPoint1,src2,ketPoint2,goodmatches,matchImg);
	namedWindow("output",CV_WINDOW_AUTOSIZE);
	imshow("output",matchImg);

	waitKey(0);
	return 0;
}

