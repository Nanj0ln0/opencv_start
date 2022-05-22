#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>

using namespace cv;
using namespace std;

const char* output_title = "Shi_Tomasi";
const char* input_title = "input";

Mat src,src_gray, dst;

int corners = 25;       //�ǵ������
int cornersMax = 200;	//�ǵ����������ֵ

void Shi_Tomasi_demo(int,void*);

int main() {

	src = imread("C:/Users/22207/Desktop/superis/jianzhuwu.JPG");
	if (!src.data)
	{
		printf("ERROR");
		return -1;
	}

	namedWindow(input_title,CV_WINDOW_AUTOSIZE);
	namedWindow(output_title,CV_WINDOW_AUTOSIZE);
	imshow(input_title,src);

	cvtColor(src,src_gray,COLOR_BGR2GRAY);

	createTrackbar("�ǵ�����",output_title,&corners,cornersMax,Shi_Tomasi_demo);
	Shi_Tomasi_demo(0, 0);

	waitKey(0);
	return 0;
}

void Shi_Tomasi_demo(int,void*) {

	//����Ҫ����5��
	if (corners<5)
	{
		corners = 5;

	}


	//�㷨����׼��
		//�ǵ�����洢
		vector<Point2f> corner;
		//�ɽ�����Сֵ����ֵ
		double qualityLeve = 0.01 ;
		//�ǵ�֮����С�ľ���
		double minDistance = 10;
		//���㵼������ؾ���ʱ������Χ
		int blockSize = 3;
		//�Ƿ�ʹ��Harris
		bool useHarris = false;
		//Ȩ��ϵ��
		int k = 3;

	//Shi-Tomasi�㷨
		goodFeaturesToTrack(src_gray,corner,corners,qualityLeve,minDistance,Mat(),blockSize,useHarris,k);

		printf("�˴μ�⹲��⵽�ǵ�����Ϊ:%d \n",corner.size());

	//��ͼ�ϻ�����
		dst = src.clone();
		for (size_t t = 0; t < corner.size(); t++)
		{
			circle(dst,corner[t],2,Scalar(0,0,0),2,8,0);

		}
		imshow(output_title,dst);

}