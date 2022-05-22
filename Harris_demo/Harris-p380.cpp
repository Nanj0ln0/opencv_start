#include<opencv2/opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;

Mat src_gray;
Mat src, dst;
int thresh = 100;//默认阈值
int thresh_max = 255;//最大阈值
void harris_demo(int,void*);

int main() {

	src = imread("C:/Users/22207/Desktop/superis/jianzhuwu.JPG");
	if (!src.data)
	{
		printf("ERROR");
		return -1;
	}
	namedWindow("imshow", CV_WINDOW_AUTOSIZE);
	namedWindow("output", CV_WINDOW_AUTOSIZE);
	imshow("imshow",src);

	cvtColor(src, src_gray,COLOR_BGR2GRAY); //转灰度
	createTrackbar("阈值","output",&thresh,thresh_max,harris_demo);
	harris_demo(0,0);
	
	//简单实现
	/*
	Mat cornerStrength;
	cornerHarris(src,cornerStrength,2,3,0.01);
	Mat harrisCorner;
	threshold(cornerStrength,harrisCorner,0.00001,255,THRESH_BINARY);
	*/

	waitKey(0);
	return 0;
}

void harris_demo(int, void*) {

	dst = Mat::zeros(src_gray.size(),CV_32FC1);

	//角点检测
	int blockSize = 2;
	int	ksize = 3;
	double k = 0.04;
	cornerHarris(src_gray, dst, blockSize,ksize,k,BORDER_DEFAULT);
	
	//最大最小值归一化
	Mat nor_dst, normScaleDst;//用于存储归一化的值
	normalize(dst,nor_dst,0,255,NORM_MINMAX,CV_32FC1,Mat());
	
	
	convertScaleAbs(nor_dst, normScaleDst);   //将计算绝对值并将结果转换为 8 位，可能可以不要


	//标记
	Mat resultImg = src.clone(); 

	//第一种实现方式
	/*
	for (int row = 0; row < resultImg.rows; row++)
	{
		uchar* currentRow = normScaleDst.ptr(row);
		for (int col = 0; col < resultImg.cols; col++)
		{
			int value = (int)*currentRow;
			if (value > thresh)
			{
				circle(resultImg,Point(col,row),2,Scalar(0,0,0),2,8,0);

			}
			currentRow++;//下一个指针
		}
	}
	*/

	//另一种实现方式
	for (int row = 0; row < nor_dst.rows; row++)
	{
		for (int col = 0; col < nor_dst.cols; col++)
		{
			if ((int)nor_dst.at<float>(row, col) > thresh)
			{
				circle(resultImg, Point(col, row), 2, Scalar(0, 0, 0), 2, 8, 0);
			}

		}

	}

	
	imshow("output", resultImg);
}
