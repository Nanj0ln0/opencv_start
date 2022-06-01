#include <opencv2/opencv.hpp>
#include <iostream>
#include <opencv2/xfeatures2d.hpp>
#include <math.h>

using namespace cv;
using namespace std;
using namespace cv::xfeatures2d;


int main() {
	Mat obj = imread("C:/Users/22207/Desktop/superis/pipei0 - 1.JPG", 0);
	Mat scene = imread("C:/Users/22207/Desktop/superis/pipei0.JPG", 0);
	if (!obj.data || !scene.data)
	{
		printf("ERROR");
		return -1;
	}
	namedWindow("obj", CV_WINDOW_AUTOSIZE);
	namedWindow("scene", CV_WINDOW_AUTOSIZE);

	imshow("obj", obj);
	imshow("scene", scene);

	//获取keypoint 和 描述子
	Ptr<Feature2D> detector = BRISK::create();
	vector<KeyPoint>KeyPoints_obj;
	vector<KeyPoint>KeyPoints_scene;
	Mat descriptor_obj,descriptor_scene;
	detector->detectAndCompute(obj,Mat(),KeyPoints_obj,descriptor_obj);
	detector->detectAndCompute(scene,Mat(),KeyPoints_scene,descriptor_scene);

	//暴力匹配
	BFMatcher matcher(NORM_L2);

	vector<DMatch>matches;
	matcher.match(descriptor_obj,descriptor_scene,matches);

	
	//筛选
	vector<DMatch>goodmatches;
	double mindist = 1000;
	double maxdist = 0;
	for (int i = 0; i < descriptor_obj.rows; i++)
	{
		double dist = matches[i].distance;
		if (dist<mindist)
		{
			mindist = dist;
		}
		if (dist > maxdist)
		{
			maxdist = dist;
		}
	}

	for (int i = 0; i < descriptor_obj.rows; i++)
	{
		double dist = matches[i].distance;
		if (dist<max(2*mindist,0.02))
		{
			goodmatches.push_back(matches[i]);;
		}
	}

	//画出描述子
	Mat matchImg;
	drawMatches(obj, KeyPoints_obj, scene, KeyPoints_scene, goodmatches, matchImg, Scalar::all(-1), Scalar::all(-1), vector<char>(), 2);

	namedWindow("matchImg");
	imshow("matchImg", matchImg);
	


	//把图像标记出来
	//预定义
	vector<Point2f>point_obj;
	vector<Point2f>point_scene;

	for (size_t i = 0; i < goodmatches.size(); i++)
	{
		point_obj.push_back(KeyPoints_obj[goodmatches[i].queryIdx].pt);
		point_scene.push_back(KeyPoints_scene[goodmatches[i].trainIdx].pt);
	}

	Mat H = findHomography(point_obj, point_scene, RANSAC);


	//定义4个角
	vector<Point2f>obj_corners(4);
	obj_corners[0] = Point(0, 0);
	obj_corners[1] = Point(obj.cols, 0);
	obj_corners[2] = Point(obj.cols, obj.rows);
	obj_corners[3] = Point(0, obj.rows);

	//定义场景里的4个角
	vector<Point2f>scene_corners(4);
	perspectiveTransform(obj_corners, scene_corners, H);

	//画框框

	line(matchImg, scene_corners[0] + Point2f(obj.cols, 0), scene_corners[1] + Point2f(obj.cols, 0), Scalar::all(-1), 2, 8, 0);
	line(matchImg, scene_corners[1] + Point2f(obj.cols, 0), scene_corners[2] + Point2f(obj.cols, 0), Scalar::all(-1), 2, 8, 0);
	line(matchImg, scene_corners[2] + Point2f(obj.cols, 0), scene_corners[3] + Point2f(obj.cols, 0), Scalar::all(-1), 2, 8, 0);
	line(matchImg, scene_corners[3] + Point2f(obj.cols, 0), scene_corners[0] + Point2f(obj.cols, 0), Scalar::all(-1), 2, 8, 0);


	namedWindow("BRISKmatchImg", CV_WINDOW_AUTOSIZE);
	imshow("BRISKmatchImg", matchImg);





	waitKey(0);
	return 0;
}
