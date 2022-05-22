#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

const char* output_title = "output";
const char* input_title = "input";

Mat src,dst;
Mat src_gray;

int thresh = 90;
int max_thresh = 255;

void harris_demo(int,void*);

int main() {
	src = imread("C:/Users/22207/Desktop/superis/jianzhuwu.JPG");
	if (!src.data)
	{
		printf("ERROR");
		return -1;
	}

	namedWindow(input_title,CV_WINDOW_AUTOSIZE);
	namedWindow(output_title, CV_WINDOW_AUTOSIZE);
	imshow(input_title,src);


	
	cvtColor(src,src_gray,CV_BGR2GRAY);


	createTrackbar("阈值",output_title,&thresh,max_thresh,harris_demo);
	harris_demo(0, 0);


	waitKey(0);
	return 0;
}

void harris_demo(int , void*) {

	Mat harrisImg = Mat::zeros(src_gray.size(),CV_32FC1);

	//角点检测
	int blocksize = 2;
	int ksize = 3;
	double k = 0.04;
	cornerHarris(src_gray ,harrisImg,blocksize , ksize ,k ,BORDER_DEFAULT);

	//归一化
	Mat norm_dst, normScaleDst;
	normalize(harrisImg,norm_dst,0 ,255,NORM_MINMAX,CV_32FC1,Mat());
	
	convertScaleAbs(norm_dst, normScaleDst);


	dst = src.clone();
	for (int row = 0; row < norm_dst.rows; row++)
	{
		for (int col = 0; col < norm_dst.cols; col++)
		{
			if ((int)norm_dst.at<float>(row,col) > thresh)
			{
				circle(dst,Point(col,row),2,Scalar(0,0,0),2,8,0);
			}

		}
		
	}
	imshow(output_title,dst);

}
