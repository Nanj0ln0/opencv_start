#include <opencv2/opencv.hpp>
#include <iostream>
#include <opencv2/xfeatures2d.hpp>
#include <math.h>

using namespace cv;
using namespace std;
using namespace cv::xfeatures2d;


int main() {
	Mat src1 = imread("C:/Users/22207/Desktop/superis/pipei0 - 1.JPG", 0);
	Mat src2 = imread("C:/Users/22207/Desktop/superis/pipei0.JPG", 0);
	if (!src1.data || !src2.data)
	{
		printf("ERROR");
		return -1;
	}

	namedWindow("input1", CV_WINDOW_AUTOSIZE);
	namedWindow("input2", CV_WINDOW_AUTOSIZE);
	imshow("input1", src1);
	imshow("input2", src2);

	//ʹ��SURF�õ�������
	int minHarris = 400;
	Ptr<SURF>detector = SURF::create(minHarris);
	vector<KeyPoint> keypoint_obj;
	vector<KeyPoint> keypoint_scene;
	Mat descritor_obj, descritor_scene;
	detector->detectAndCompute(src1,Mat(),keypoint_obj,descritor_obj);
	detector->detectAndCompute(src2,Mat(),keypoint_scene,descritor_scene);

	//match flannƥ��
	FlannBasedMatcher matcher;
	vector<DMatch> matches;
	matcher.match(descritor_obj,descritor_scene,matches);

	//ɸѡ
	double mindist=1000;
	double maxdist = 0;
	for (int i = 0; i < descritor_obj.rows; i++)
	{
		double dist = matches[i].distance;
		if (dist > maxdist)
		{
			maxdist = dist;
		}
		if (dist<mindist)
		{
			mindist = dist;
		}
	}

	printf("������Ϊ��%f����С����Ϊ��%f\n", maxdist, mindist);

	vector<DMatch> goodmatches;
	for (int i = 0; i < descritor_obj.rows; i++)
	{
		double dist = matches[i].distance;
		if (dist < max(2*mindist,0.02))
		{
			goodmatches.push_back(matches[i]);
		}

	}

	Mat matchImg;
	drawMatches(src1,keypoint_obj,src2,keypoint_scene,goodmatches,matchImg,Scalar::all(-1),Scalar::all(-1),Mat(),2);



	vector<Point2f> obj;  //��ҪѰ�ҵĶ���
	vector<Point2f> objInScene;  //�����ڳ�����  
	
	for (size_t t = 0; t < goodmatches.size(); t++)
	{
		obj.push_back(keypoint_obj[goodmatches[t].queryIdx].pt);
		objInScene.push_back(keypoint_scene[goodmatches[t].trainIdx].pt);
	}
	
	Mat H = findHomography(obj,objInScene,RANSAC);  //ʹ��RANSAC�㷨���������һ�£�����һ��͸�ӱ任�ľ���
	
	//�ȶ���������4����(��Ʒ����ҪѰ�ҵĶ���)
	vector<Point2f>obj_corners(4);
	obj_corners[0] = Point(0, 0);
	obj_corners[1] = Point(src1.cols, 0);
	obj_corners[2] = Point(src1.cols,src1.rows);
	obj_corners[3] = Point(0, src1.rows);
	//�ٶ��峡��������4����
	vector<Point2f>scene_corners(4);
	//��ͼ�����͸�ӱ任
	perspectiveTransform(obj_corners, scene_corners, H);

	//�����
	line(matchImg, scene_corners[0] + Point2f(src1.cols, 0), scene_corners[1] + Point2f(src1.cols, 0), Scalar::all(-1), 2 ,8, 0);
	line(matchImg, scene_corners[1] + Point2f(src1.cols, 0), scene_corners[2] + Point2f(src1.cols, 0), Scalar::all(-1), 2, 8, 0);
	line(matchImg, scene_corners[2] + Point2f(src1.cols, 0), scene_corners[3] + Point2f(src1.cols, 0), Scalar::all(-1), 2, 8, 0);
	line(matchImg, scene_corners[3] + Point2f(src1.cols, 0), scene_corners[0]+ Point2f(src1.cols, 0), Scalar::all(-1), 2, 8, 0);
	



	namedWindow("matchImg", CV_WINDOW_AUTOSIZE);
	imshow("matchImg", matchImg);
	waitKey(0);
	return 0;
}
