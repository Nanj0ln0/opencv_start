#include <opencv2/opencv.hpp>
#include <iostream>
#include <opencv2/xfeatures2d.hpp>


using namespace cv;
using namespace std;
using namespace cv::xfeatures2d;

const char* input = "input_picture";

int	main() {
	Mat src = imread("C:/Users/22207/Desktop/superis/jianzhuwu.JPG");
	if (!src.data)
	{
		printf("ERROR");
		return -1;
	}
	namedWindow(input, CV_WINDOW_AUTOSIZE);
	imshow(input,src);
	//ת�Ҷ� 
	Mat src_gray;
	cvtColor(src,src_gray,COLOR_BGR2GRAY);

	//��ȡ��Ⱥ͸߶�
	int width= src_gray.cols;
	int height = src_gray.rows;


	
	//����LBPͼƬ��-2����Ϊ�ڼ���ʱ���õ�3*3�����ӣ���Χ����һȦ��������
	Mat LBPImg= Mat::zeros(src_gray.rows -2, src_gray.cols -2,CV_8UC1);

	for (int row = 1; row < height - 1; row++) //
	{
		for (int col = 1; col < width - 1; col++) //width-1
		{
			uchar center = src_gray.at<uchar>(row, col);
			uchar code = 0;
			code |= (src_gray.at<uchar>(row - 1, col - 1) > center) << 7;
			//cout << bitset<16>(code) << endl;
			code |= (src_gray.at<uchar>(row - 1, col) > center) << 7;
			//cout << bitset<16>(code) << endl;
			code |= (src_gray.at<uchar>(row - 1, col + 1) > center) << 7;
			//cout << bitset<16>(code) << endl;
			code |= (src_gray.at<uchar>(row , col - 1) > center) << 7;
			//cout << bitset<16>(code) << endl;
			code |= (src_gray.at<uchar>(row , col + 1) > center) << 7;
			//cout << bitset<16>(code) << endl;
			code |= (src_gray.at<uchar>(row + 1, col - 1) > center) << 7;
			//cout << bitset<16>(code) << endl;
			code |= (src_gray.at<uchar>(row + 1, col ) > center) << 7;
			//cout << bitset<16>(code) << endl;
			code |= (src_gray.at<uchar>(row + 1, col + 1) > center) << 7;
			//cout << bitset<16>(code) << endl;
			LBPImg.at<uchar>(row - 1, col - 1) = code;
		//	printf("%d",code);
		}

	}
	imshow("LBP output",LBPImg);

	waitKey(0);
	return 0;
}