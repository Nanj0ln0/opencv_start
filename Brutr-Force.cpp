#include <opencv2/opencv.hpp>
#include <iostream>
#include <opencv2/xfeatures2d.hpp>

using namespace cv;
using namespace std;
using namespace cv::xfeatures2d;


int main() {
	Mat src = imread("C:/Users/22207/Desktop/superis/pipei0.JPG",0);
	Mat pipei = imread("C:/Users/22207/Desktop/superis/pipei1.JPG",0);
	if (!src.data||!pipei.data)
	{
		printf("ERROR");
		return -1;
	}

	namedWindow("input", CV_WINDOW_AUTOSIZE);
	namedWindow("input1", CV_WINDOW_AUTOSIZE);
	namedWindow("pipei",CV_WINDOW_AUTOSIZE);
	imshow("input", src);
	imshow("input1", pipei);
	
	//SURF����׼��
	int minHessian = 400;
	Ptr<SURF>detector = SURF::create(minHessian);
	vector<KeyPoint> keypoint1;
	vector<KeyPoint> keypoint2;
	//��ȡ������
	Mat P1, P2;
	detector->detectAndCompute(src, Mat(),keypoint1,P1);
	detector->detectAndCompute(pipei, Mat(), keypoint2, P2);
	
	//����ƥ��
	BFMatcher matcher;
	vector<DMatch> matches;
	matcher.match(P1,P2, matches);
	
	//����ƥ���
	Mat matchImg;
	drawMatches(src,keypoint1,pipei,keypoint2, matches, matchImg);
	imshow("pipei", matchImg);
	
	waitKey(0);
	return 0;
}