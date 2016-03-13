#pragma once

#include <opencv2/opencv.hpp>
#include <opencv\highgui.h>
#include <windows.h>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

class Controller
{
private:
	Point targetCenter;
	Point laserPosition;
	
	
public:
	DirectionEnum lastDirection;

	Controller(Point targetCenterr,Point laserPositionn);
	~Controller();

	DirectionEnum countControlValue();
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