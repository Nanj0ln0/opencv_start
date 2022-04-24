#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>

using namespace cv;
using namespace std;

const char input[] = "input_window";
const char output[] = "output_window";

Mat imgResult;
Mat imgLaplance;
Mat src, dst;


void changeBackcolor(void);

int main() {
	src = imread("D:/OpenCV/picture zone/YB.jpg");
	if (!src.data)
	{
		printf("ERROR");
		return -1;
	}
	namedWindow(input,CV_WINDOW_AUTOSIZE);
	namedWindow("二值图像", CV_WINDOW_AUTOSIZE);
	imshow(input,src);

	
	//changeBackcolor();//变换图片背景色
	imshow("变换图片背景色", src);

	blur(src,src,Size(3,3),Point(-1,-1));
	imshow("降噪", src);

	
	//图像锐化凸显边缘
	Mat kernel = (Mat_<float>(3, 3) << 1, 1, 1, 1, -5, 1, 1, 1, 1);
	
	Mat sharp = src;
	filter2D(src, imgLaplance, CV_32F,5, Point(-1, -1), 0);
	src.convertTo(sharp, CV_32F);
	imgResult = sharp - imgLaplance;

	//显示
	imgResult.convertTo(imgResult, CV_8UC3);   //converTo   转数据类型用的
	imgLaplance.convertTo(imgLaplance, CV_8UC3);
	imgResult = src;
	imshow("图像锐化凸显边缘", imgResult);

	

	//转二值图像
	Mat binary;
	cvtColor(src, imgResult, CV_BGR2GRAY);
	//Canny(imgResult,binary,0,255);
	threshold(imgResult, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);
	imshow("二值图像", binary);

	//开运算
	Mat open;
	morphologyEx(binary,open,CV_MOP_OPEN,kernel,Point(-1,-1));
	imshow("开运算",open);


	//距离变换 
	Mat dissImg;
	distanceTransform(binary, dissImg, DIST_L1, 3, 5);
	normalize(dissImg, dissImg, 0, 1, NORM_MINMAX);
	imshow("距离变换", dissImg);

	//将距离变换后的结果再次二值化，得到标记
	threshold(dissImg, dissImg, 0, 1.0, THRESH_BINARY);
	imshow("标记", dissImg);

	//对标记腐蚀
	Mat kernel2 = Mat::ones(13, 13, CV_8UC1);
	erode(dissImg, dissImg, kernel2);
	imshow("对标记腐蚀", dissImg);

	//发现轮廓
	Mat dist_8u;
	dissImg.convertTo(dist_8u, CV_8U);
	vector<vector<Point>> contours;
	findContours(dist_8u, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));

	//绘制轮廓，画在新的图上
	Mat markers = Mat::zeros(dissImg.size(), CV_32SC1);
	for (size_t i = 0; i < contours.size(); i++)
	{
		drawContours(markers, contours, static_cast<int>(i), Scalar::all(static_cast<int>(i) + 1));
	}
	circle(markers, Point(5, 5), 3, CV_RGB(255, 255, 255), -1);
	imshow("绘制轮廓，画在新的图上", markers * 1000);


	//分水岭变换
	watershed(src, markers);
	Mat mark = Mat::zeros(markers.size(), CV_8UC1);

	markers.convertTo(mark, CV_8UC1);
	bitwise_not(mark, mark);
	imshow("分水岭变换", mark);

	//上色

	vector<Vec3b> colors;
	for (size_t i = 0; i < contours.size(); i++) {
		int r = theRNG().uniform(0, 255);
		int g = theRNG().uniform(0, 255);
		int b = theRNG().uniform(0, 255);
		colors.push_back(Vec3b((uchar)b, (uchar)g, (uchar)r));
	}



	dst = Mat::zeros(markers.size(),CV_8UC3);
	for (int row = 0; row < markers.rows; row++)
	{
		for (int col = 0; col < markers.cols; col++)
		{
			int index = markers.at<int>(row, col);
			if (index > 0 && index <= static_cast<int>(contours.size())) {
				dst.at<Vec3b>(row, col) = colors[index - 1];
			}
			else {
				dst.at<Vec3b>(row, col) = Vec3b(0, 0, 0);
			}

		}
	}

	imshow(output, dst);

	waitKey(0);
	return 0;
}

void changeBackcolor() {
	for (int i = 0; i < src.rows; i++) //行
	{
		for (int k = 0; k < src.cols; k++)//列
		{
				if (src.at<Vec3b>(i, k) == Vec3b(255,255,255))
				{
					src.at<Vec3b>(i, k)[0] = 0;
					src.at<Vec3b>(i, k)[1] = 0;
					src.at<Vec3b>(i, k)[2] = 0;
				}
		}
	}
	return;
}





