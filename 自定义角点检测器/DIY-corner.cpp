#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>

using namespace cv;
using namespace std;

const char* input_title = "input_picture";
const char* Harris_demo = "Harris_demo";
const char* ShiTomasi_demo = "ShiTomasi_demo";

Mat harris_dst, harrisImg , shiTomasiRsp;
Mat src, Hdst,Sdst;

//harris ����
double harris_min_rsp, harris_max_rsp;
int Harris_quality = 30;
int Harris_qualitu_max = 100;

//shitomasi����
double shiTomasi_min_rsp, shiTomasi_max_rsp;
int shiTomasi_quality = 30;
int shiTomasi_qualitu_max = 100;

void DIY_Harris(int,void*);
void DIY_ShiTomasi(int, void*);

int main() {
	src = imread("C:/Users/22207/Desktop/superis/jianzhuwu.JPG");
	if (!src.data)
	{
		printf("ERROR");
		return -1;
	}

	namedWindow(input_title, CV_WINDOW_AUTOSIZE);
	namedWindow(Harris_demo, CV_WINDOW_AUTOSIZE);
	namedWindow(ShiTomasi_demo,CV_WINDOW_AUTOSIZE);
	imshow(input_title,src);

	Mat src_gray;
	cvtColor(src,src_gray,COLOR_BGR2GRAY);


//����cornerEigenValsAndVecs()������minMaxLoc()���������ģ��Harris�ǵ���Ĵ���
	//�����趨
	int blockSize = 3;
	int ksize = 3;
	double k = 0.04;
	harris_dst = Mat::zeros(src.size(),CV_32FC(6));
	harrisImg = Mat::zeros(src.size(), CV_32FC1);
	//��������ֵ
	cornerEigenValsAndVecs(src_gray,harris_dst,blockSize,ksize,BORDER_DEFAULT);
	//������Ӧ
	for (int row = 0; row < harris_dst.rows; row++)
	{
		for (int  col = 0; col < harris_dst.cols; col++)
		{
			double lamda1 = harris_dst.at<Vec6f>(row, col)[0];
			double lamda2 = harris_dst.at<Vec6f>(row, col)[1];
			harrisImg.at<float>(row, col) = lamda1 * lamda2 - k * pow((lamda1 + lamda2), 2);
		}
	}
	minMaxLoc(harrisImg,&harris_min_rsp,&harris_max_rsp,0,0,Mat());

	//ʹ��barȥ������Ӧ�ȼ�RSP
	createTrackbar("DIY-Harris", Harris_demo,&Harris_quality, Harris_qualitu_max,DIY_Harris);
	DIY_Harris(0, 0);



// ����cornerMinEigenVal()������minMaxLoc()���������ģ��ShiTomasi�ǵ���Ĵ���
	//������С����ֵ
	shiTomasiRsp = Mat::zeros(src.size(),CV_32FC1);
	cornerMinEigenVal(src_gray,shiTomasiRsp,blockSize,ksize,BORDER_DEFAULT);
	minMaxLoc(shiTomasiRsp, &shiTomasi_min_rsp, &shiTomasi_max_rsp, 0, 0, Mat());
	createTrackbar("DIY-shiTomasi",ShiTomasi_demo, &shiTomasi_quality, shiTomasi_qualitu_max, DIY_ShiTomasi);
	DIY_ShiTomasi(0, 0);

	waitKey(0);
	return 0;

}
void DIY_Harris(int, void*) {

	if (Harris_quality<10)
	{
		Harris_quality = 10;
	}

	Hdst = src.clone();

	float t = harris_min_rsp +(((double)Harris_quality / Harris_qualitu_max)*(harris_max_rsp-harris_min_rsp));
	for (int row = 0; row < harris_dst.rows; row++)
	{
		for (int col = 0; col < harris_dst.cols; col++)
		{
			float v = harrisImg.at<float>(row, col);
			if (v>t)
			{
				circle(Hdst, Point(col,row),2,Scalar(0,0,0),2,8,0);
			}
		
		}
	}
	imshow(Harris_demo,Hdst);
}


void DIY_ShiTomasi(int, void*) {

	if (shiTomasi_quality < 20)
	{
		shiTomasi_quality = 20;
	}

	Sdst = src.clone();

	float t = shiTomasi_min_rsp + (((double)shiTomasi_quality / shiTomasi_qualitu_max) * (shiTomasi_max_rsp - shiTomasi_min_rsp));
	for (int row = 0; row < src.rows; row++)
	{
		for (int col = 0; col < src.cols; col++)
		{
			float v = shiTomasiRsp.at<float>(row, col);
			if (v > t)
			{
				circle(Sdst, Point(col, row), 2, Scalar(0, 0, 0), 2, 8, 0);
			}

		}
	}
	imshow(ShiTomasi_demo, Sdst);



}