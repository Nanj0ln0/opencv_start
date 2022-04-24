#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>

using namespace cv;
using namespace std;

int main() {
	const int r = 100;
	Mat src = Mat::zeros(r*4,r*4,CV_8UC1);

	vector<Point> vert(6);
	vert[0] = Point(3 * r / 2,static_cast<int>(1.34*r));
	vert[1] = Point(1*r,2*r);
	vert[2] = Point(3*r/2, static_cast<int>(2.866 * r));
	vert[3] = Point(5*r/2, static_cast<int>(2.866 * r));
	vert[4] = Point(3*r,2*r);
	vert[5] = Point(5*r/2, static_cast<int>(1.34 * r));

	for (int i = 0; i < 6; i++)
	{
		line(src,vert[i],vert[(i+1)%6],Scalar(255),3,8,0);
	}

	namedWindow("1", CV_WINDOW_AUTOSIZE);
	imshow("1",src);

	vector<vector<Point>> contours;
	vector<Vec4i> hierachy;

	Mat src_copy = src.clone();

	findContours(src_copy,contours,hierachy,RETR_TREE,CHAIN_APPROX_SIMPLE,Point(0,0));

	Mat raw_dist = Mat(src_copy.size(),CV_32FC1);
	for (int row = 0; row < src_copy.rows; row++)
	{
		for (int  col = 0; col < src_copy.cols; col++)
		{
			double dist = pointPolygonTest(contours[0],Point2f((float)col,(float)row),true);
			raw_dist.at<float>(row, col) = static_cast<float>(dist);
		}

	}

	double max, min;
	minMaxLoc(raw_dist, &min, &max,0,0,Mat());

	Mat drawImg = Mat::zeros(src.size(),CV_8UC3);

	for (int row = 0; row < src_copy.rows; row++)
	{
		for (int col = 0; col < src_copy.cols; col++)
		{
			float dist = raw_dist.at<float>(row, col);
			if (dist>0)
			{
				drawImg.at<Vec3b>(row, col)[0] = (uchar)( abs(1.0 - (dist / max)) * 255);
			}
			else if (dist<0)
			{
				drawImg.at<Vec3b>(row, col)[2] = (uchar)(abs(1.0 - (dist / max) )* 255);
			}
			else
			{
				drawImg.at<Vec3b>(row, col)[0] = (uchar)(abs(255 - dist) );
				drawImg.at<Vec3b>(row, col)[1] = (uchar)(abs(255 - dist) );
				drawImg.at<Vec3b>(row, col)[2] = (uchar)(abs(255 - dist) );


			}
		}

	}


	imshow("2", drawImg);






	waitKey(0); 
	return 0;

}