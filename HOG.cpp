#include <opencv2/opencv.hpp>
#include <iostream>
#include <opencv2/xfeatures2d.hpp>

using namespace cv;
using namespace std;
using namespace cv::xfeatures2d;

const char* input_title = "input";

int main() {
	Mat src = imread("C:/Users/22207/Desktop/superis/mans-2.jpg");
	if (!src.data)
	{
		printf("ERROR");
		return -1;
	}

	namedWindow(input_title,CV_WINDOW_AUTOSIZE);
	imshow(input_title,src);

	//简单实现HOG检测
	/*
	  //改变圆图像尺寸大小   64*128
	Mat src_resize;         
	resize(src,src_resize,Size(64,128));
	  //转变图像色彩空间至灰度
	Mat src_gray;
	cvtColor(src_resize,src_gray,COLOR_BGR2GRAY);

	 //定义HOG的描述子  detector
	HOGDescriptor detector(Size(64,128),Size(16,16),Size(8,8),Size(8,8),9);
	//计算的参数定义
	vector<float> descriptors;  //存放特征点的空间
	vector<Point> locations;	//存放
	 //使用描述子的comput计算功能
	detector.compute(src_gray,descriptors,Size(0,0),Size(0,0),locations); //窗口的步长使用(0,0)的默认值，padding(0,0)默认值
	printf("特征点有%d个",descriptors.size());
	*/
	

	//HOG+SVM行人检测
	HOGDescriptor hog = HOGDescriptor();
	hog.setSVMDetector(hog.getDefaultPeopleDetector());

	vector<Rect> foundLocations;
	hog.detectMultiScale(src,foundLocations,0,Size(8,8),Size(32,32),1.05,2);
	for (size_t t = 0; t < foundLocations.size(); t++)
	{
		rectangle(src,foundLocations[t],Scalar(0,0,255),2,8,0);

	}

	namedWindow("HOG+SVM", CV_WINDOW_AUTOSIZE);
	imshow("HOG+SVM",src);


	waitKey(0);
	return 0;

}