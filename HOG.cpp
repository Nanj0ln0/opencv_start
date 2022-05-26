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

	//��ʵ��HOG���
	/*
	  //�ı�Բͼ��ߴ��С   64*128
	Mat src_resize;         
	resize(src,src_resize,Size(64,128));
	  //ת��ͼ��ɫ�ʿռ����Ҷ�
	Mat src_gray;
	cvtColor(src_resize,src_gray,COLOR_BGR2GRAY);

	 //����HOG��������  detector
	HOGDescriptor detector(Size(64,128),Size(16,16),Size(8,8),Size(8,8),9);
	//����Ĳ�������
	vector<float> descriptors;  //���������Ŀռ�
	vector<Point> locations;	//���
	 //ʹ�������ӵ�comput���㹦��
	detector.compute(src_gray,descriptors,Size(0,0),Size(0,0),locations); //���ڵĲ���ʹ��(0,0)��Ĭ��ֵ��padding(0,0)Ĭ��ֵ
	printf("��������%d��",descriptors.size());
	*/
	

	//HOG+SVM���˼��
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