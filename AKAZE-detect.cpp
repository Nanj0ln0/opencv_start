#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
	Mat obj = imread("C:/Users/22207/Desktop/superis/pipei0 - 1.JPG",0);
	Mat scene = imread("C:/Users/22207/Desktop/superis/pipei0.JPG", 0);
	if (!obj.data||!scene.data)
	{
		printf("ERROR");
		return -1;
	}
	
	imshow("obj",obj);
	imshow("scene", scene);

	//kaze detection
	Ptr<AKAZE>detector = AKAZE::create();
	vector<KeyPoint>KeyPoints_obj;
	vector<KeyPoint>KeyPoints_scene;
	Mat descritor_obj, descritor_scene;  //√Ë ˆ◊”
	detector->detectAndCompute(obj,Mat(),KeyPoints_obj,descritor_obj);
	detector->detectAndCompute(scene,Mat(),KeyPoints_scene,descritor_scene);

	//match flann∆•≈‰  √Ë ˆ◊”
	FlannBasedMatcher matcher;
	vector<DMatch> matches;
	matcher.match(descritor_obj,descritor_scene,matches);
	
	

	waitKey(0);
	return 0;

}