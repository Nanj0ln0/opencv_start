#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {

	//将训练数据拿过来
	string cascadeFilePath = "C:\\Program Files\\opencv\\opencv\\build\\etc\\haarcascades\\haarcascade_frontalface_alt.xml";
	//定义级联检测器
	CascadeClassifier face_cascade;
	//加载训练数据
	if (!face_cascade.load(cascadeFilePath)) {
		printf("ERROR");
		return -1;
	};

	Mat src = imread("C:/Users/22207/Desktop/superis/man.jpg");
	Mat src_gray; 
	cvtColor(src,src_gray,COLOR_BGR2GRAY);
	//直方图均衡化，有利于检出
	equalizeHist(src_gray,src_gray);

	vector<Rect>face;
	//灰度图，脸部数据存储空间，每次尺度空间扩张1.1倍, 2 ,0|CASCADE_SCALE_IMA（视频）,小于30,30则忽略，不认为是人脸
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