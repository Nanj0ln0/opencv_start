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
		printf("ERROR");
		return -1;
	}
	namedWindow("input_title", CV_WINDOW_AUTOSIZE);
	namedWindow("outpoint", CV_WINDOW_AUTOSIZE);
	imshow("input_title",src);

	Mat sumii = Mat::zeros(src.rows+1,src.cols+1,CV_32FC1);
	Mat sqsumii = Mat::zeros(src.rows + 1, src.cols + 1, CV_64FC1);
	integral(src,sumii,sqsumii);

	Mat iiresult,sqsumResult;
	normalize(sumii,iiresult,0,255,NORM_MINMAX,CV_8UC1,Mat());
	normalize(sumii, sqsumResult, 0, 255, NORM_MINMAX, CV_8UC1, Mat());
	imshow("outpoint",iiresult);
	imshow("sqsumResult", sqsumResult);

	waitKey(0);
	return 0;

}