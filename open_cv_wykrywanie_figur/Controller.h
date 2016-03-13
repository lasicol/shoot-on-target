#pragma once
#include <opencv2/opencv.hpp>
#include <opencv\highgui.h>
#include <windows.h>

using namespace std;
using namespace cv;

enum DirectionEnum;

class Controller 
{
	
public:
	
	DirectionEnum lastDirection;
	Controller();
	~Controller();
	DirectionEnum CountDirction(Point* targetCenter, Point* laserPosition);

	
};



enum DirectionEnum
{
	UP,
	UP_RIGHT,
	RIGHT,
	DOWN_RIGHT,
	DOWN,
	DOWN_LEFT,
	LEFT,
	UP_LEFT,
};