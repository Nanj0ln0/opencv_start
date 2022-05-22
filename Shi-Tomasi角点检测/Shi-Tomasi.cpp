#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>

using namespace cv;
using namespace std;

const char* output_title = "Shi_Tomasi";
const char* input_title = "input";

Mat src,src_gray, dst;

int corners = 25;       //角点的数量
int cornersMax = 200;	//角点数量的最大值

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

	createTrackbar("角点数量",output_title,&corners,cornersMax,Shi_Tomasi_demo);
	Shi_Tomasi_demo(0, 0);

	waitKey(0);
	return 0;
}

void Shi_Tomasi_demo(int,void*) {

	//最少要检测出5个
	if (corners<5)
	{
		corners = 5;

	}


	//算法参数准备
		//角点坐标存储
		vector<Point2f> corner;
		//可接受最小值特征值
		double qualityLeve = 0.01 ;
		//角点之间最小的距离
		double minDistance = 10;
		//计算导数自相关矩阵时的领域范围
		int blockSize = 3;
		//是否使用Harris
		bool useHarris = false;
		//权重系数
		int k = 3;

	//Shi-Tomasi算法
		goodFeaturesToTrack(src_gray,corner,corners,qualityLeve,minDistance,Mat(),blockSize,useHarris,k);

		printf("此次检测共检测到角点数量为:%d \n",corner.size());

	//在图上画出来
		dst = src.clone();
		for (size_t t = 0; t < corner.size(); t++)
		{
			circle(dst,corner[t],2,Scalar(0,0,0),2,8,0);

		}
		imshow(output_title,dst);

}