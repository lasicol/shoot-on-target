#pragma once

#include <opencv2/opencv.hpp>
#include <opencv\highgui.h>
#include <windows.h>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

class Control
{
private:
	Point targetCenter;
	Point laserPosition;


public:
	DirectionEnum lastDirection;

	Control(Point targetCenterr, Point laserPositionn);
	~Control();

	void countControlValue();
};

enum DirectionEnum
{
	UP=0,
	UP_RIGHT,
	RIGHT,
	DOWN_RIGHT,
	DOWN,
	DOWN_LEFT,
	LEFT,
	UP_LEFT,
};