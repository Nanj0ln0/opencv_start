#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

//参数准备
Mat src, src_gray;
const char* input_title = "inputImage";
const char* shiTomasi_window = "shiTomasi";
const char* cornerSubpix_window = "亚像素角点检测";

//shiTomasi 参数
vector<Point2f> corner;
int corners = 50;
double qualituLevel = 0.01;
double minDistance = 10;
int blockSize = 3;
bool useHarris = false;
double k;

//滑动条参数准备
void cornerSubpix_demo(int,void*);
int maxCorners=200;



int main() {
	src = imread("C:/Users/22207/Desktop/superis/jianzhuwu.JPG");
	if (!src.data)
	{
		printf("ERROR");
		return -1;
	}
	
	namedWindow(input_title,CV_WINDOW_AUTOSIZE);
	namedWindow(shiTomasi_window,CV_WINDOW_AUTOSIZE);
	imshow(input_title,src);

	cvtColor(src,src_gray,COLOR_BGR2GRAY);
	
	createTrackbar("角点数量",shiTomasi_window,&corners,maxCorners,cornerSubpix_demo);
	cornerSubpix_demo(0, 0);
	
	waitKey(0);
	return 0;
}
void cornerSubpix_demo(int, void*) {
	if (corners < 5)
	{
		corners = 5;

	}
	goodFeaturesToTrack(src_gray, corner, corners, qualituLevel, minDistance,Mat(),blockSize,useHarris,k);
	cout << "共有多少个角点：" << corner.size() << endl;

	//标出shitomasi
	Mat ShiDst = src.clone();
	for (int t = 0; t < corner.size(); t++)
	{
		
			circle(ShiDst,corner[t],2,Scalar(0,0,0),2,8,0); 

	}

	imshow(shiTomasi_window,ShiDst);

	//亚像素角点参数准备
	Size winsize = Size(5, 5);
	Size zeroZone = Size(-1, -1);
	TermCriteria tc = TermCriteria(TermCriteria::EPS + TermCriteria::MAX_ITER,40,0.001);
	cornerSubPix(src_gray,corner,winsize,zeroZone,tc);

	for (size_t i = 0; i < corner.size(); i++)
	{
		cout << (i + 1) << ".point[x,y]" << corner[i].x << "." << corner[i].y << endl;


	}
}
