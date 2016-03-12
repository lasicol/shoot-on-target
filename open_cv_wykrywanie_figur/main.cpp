
#include <opencv2/opencv.hpp>
#include <opencv\highgui.h>
#include <windows.h>
#include "Target.h"


using namespace std;
using namespace cv;


string const fileName = "tarcza//test (3).jpg";
string const windowsNames[2] = {"Source","Output Image"};


Mat src, src_gray, img, frame;
Mat dst, detected_edges, imgFinal;




/** @function main */
int main(int argc, char** argv)
{
	VideoCapture capture = VideoCapture(0);
	/// Load an image
	src = imread(fileName);

	if (!src.data)
	{
		return -1;
	}

	namedWindow(windowsNames[0], CV_WINDOW_AUTOSIZE);
	namedWindow(windowsNames[1], CV_WINDOW_AUTOSIZE);
	imshow(windowsNames[0], src);
	/// Create a matrix of the same type and size as src (for dst)
	dst.create(src.size(), src.type());
	//circle(&src);


	Target target;

	//target.tuneLaserColorRatio(src);

	/*capture >> frame;
	frame.copyTo(img);
	target.tuneThreshold(img);*/

	//target.DetectTarget(src, &dst);
	//target.findLaser(dst, &dst);
	//imshow(windowsNames[1], dst);

	target.setRadiusShild(120);
	//target.setCannyThresh(30, 90);
	while (waitKey(10) != 27)
	{
		capture >> frame;
		frame.copyTo(img);
		if (target.DetectTarget(img, &dst))
		{
			target.findLaser(img, &imgFinal);
			imshow(windowsNames[1], imgFinal);
		}
		imshow(windowsNames[0], img);
		
	}


	waitKey(0);

	return 0;
}
