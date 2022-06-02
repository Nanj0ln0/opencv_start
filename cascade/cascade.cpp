#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {

	//��ѵ�������ù���
	string cascadeFilePath = "C:\\Program Files\\opencv\\opencv\\build\\etc\\haarcascades\\haarcascade_frontalface_alt.xml";
	//���弶�������
	CascadeClassifier face_cascade;
	//����ѵ������
	if (!face_cascade.load(cascadeFilePath)) {
		printf("ERROR");
		return -1;
	};

	Mat src = imread("C:/Users/22207/Desktop/superis/man.jpg");
	Mat src_gray; 
	cvtColor(src,src_gray,COLOR_BGR2GRAY);
	//ֱ��ͼ���⻯�������ڼ��
	equalizeHist(src_gray,src_gray);

	vector<Rect>face;
	//�Ҷ�ͼ���������ݴ洢�ռ䣬ÿ�γ߶ȿռ�����1.1��, 2 ,0|CASCADE_SCALE_IMA����Ƶ��,С��30,30����ԣ�����Ϊ������
	face_cascade.detectMultiScale(src_gray,face,1.1,2,0,Size(30,30));

	for (size_t i = 0; i < face.size(); i++)
	{
		rectangle(src,face[i],Scalar(0,0,255),2,8,0);
	}
	namedWindow("face", CV_WINDOW_AUTOSIZE);
	imshow("face",src);


	waitKey(0);
	return 0;

}