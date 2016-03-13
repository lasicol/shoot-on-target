
#include <opencv2/opencv.hpp>
#include <opencv\highgui.h>
#include <windows.h>
#include "Target.h"
#include "Controller.h"

using namespace std;
using namespace cv;


string const fileName = "tarcza//kolor.jpg";
string const windowsNames[2] = {"Source","Output Image"};


Mat src, src_gray, img, frame;
Mat dst, detected_edges, imgFinal;


static const string EnumStrings[] = { "UP",
"UP_RIGHT",
"RIGHT",
"DOWN_RIGHT",
"DOWN",
"DOWN_LEFT",
"LEFT",
"UP_LEFT" };
//DirectionEnum direct;



/** @function main */
int main(int argc, char** argv)
{
	VideoCapture capture = VideoCapture(1);

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
	Controller controller;
	DirectionEnum direct;

	//target.tuneLaserColorRatio(src);

	/*capture >> frame;
	frame.copyTo(img);
	target.tuneThreshold(img);*/

	//target.DetectTarget(src, &dst);
	//target.findLaser(dst, &dst);
	//imshow(windowsNames[1], dst);

	//target.setRadiusShild(120);
	target.setLaserColorRatio(110, 179, 10, 159, 176, 255); //143, 179, 10, 159, 176, 255

	////target.setCannyThresh(30, 90);
	while (waitKey(30) != 27)
	{
		capture >> frame;
		frame.copyTo(img);
		if (target.DetectTarget(img, &dst))
		{
			target.findLaser(img, &imgFinal);
			Point center = target.getTargetCenter();
			Point laser = target.getLaserPosition();
			//Controller controller(target.getTargetCenter,target.getLaserPosition);
			direct = controller.CountDirction(&center, &laser);
			cout << EnumStrings[controller.lastDirection] << endl;
			//cout << target.getLaserPosition()<<endl;
			imshow(windowsNames[1], imgFinal);

		}
		imshow(windowsNames[0], dst);
	}


	waitKey(0);

	return 0;
}
