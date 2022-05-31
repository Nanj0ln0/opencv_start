#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>
#include <opencv2/xfeatures2d.hpp>

using namespace cv;
using namespace std;
using namespace cv::xfeatures2d;

int main() {
	Mat obj = imread("C:/Users/22207/Desktop/superis/pipei0 - 1.JPG",0);
	Mat scene = imread("C:/Users/22207/Desktop/superis/pipei0.JPG", 0);
	if (!obj.data||!scene.data)
	{
		printf("ERROR");
		return -1;
	}
	namedWindow("obj",CV_WINDOW_AUTOSIZE);
	namedWindow("scene",CV_WINDOW_AUTOSIZE);

	imshow("obj",obj);
	imshow("scene", scene);

	//kaze detection
	Ptr<AKAZE>detector = AKAZE::create();
	vector<KeyPoint>KeyPoints_obj;
	vector<KeyPoint>KeyPoints_scene;
	Mat descritor_obj, descritor_scene;  //描述子
	detector->detectAndCompute(obj,Mat(),KeyPoints_obj,descritor_obj);
	detector->detectAndCompute(scene,Mat(),KeyPoints_scene,descritor_scene);

	//matching flann匹配  描述子
	FlannBasedMatcher matcher(new flann::LshIndexParams(20, 10, 2));
	//FlannBasedMatcher matcher;
	vector<DMatch> matches;
	matcher.match(descritor_obj,descritor_scene,matches,Mat());
	
	
	//画出描述子
	Mat matchesImg;
	drawMatches(obj,KeyPoints_obj,scene,KeyPoints_scene,matches,matchesImg);
	namedWindow("marchesImg",CV_WINDOW_AUTOSIZE);
	imshow("marchesImg",matchesImg);
	
	
	vector<DMatch>goodmatches;
	double maxdist = 0;
	double mindist = 10000;
	for (int i = 0; i < descritor_obj.rows; i++)
	{
		double dise = matches[i].distance;
		if (dise < mindist)
		{
			mindist = dise;
		}
		if (dise>maxdist)
		{
			maxdist = dise;
		}
	}
	printf("最小距离为%f,最大距离为%f",mindist, maxdist);
	
	for (int t = 0; t < descritor_obj.rows; t++)
	{
		double dist = matches[t].distance;
		if (dist < max(2*mindist,0.02))
		{
			goodmatches.push_back(matches[t]);

		}

	}
	
	Mat akazematchImg;
	drawMatches(obj,KeyPoints_obj,scene,KeyPoints_scene,goodmatches,akazematchImg,Scalar::all(-1), Scalar::all(-1),vector<char>(),2);
	imshow("match",akazematchImg);
	




	waitKey(0);
	return 0;

}