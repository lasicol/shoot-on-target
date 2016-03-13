#pragma once
#include <opencv2/opencv.hpp>
#include <opencv\highgui.h>
#include <windows.h>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

class Target
{
private:
	Mat target;
	int r_shild;
	Point *targetCenter, *laser; //srodek wykrytej tarczy, laser
	
	int lowerb, upperb; 
	int min_radius, max_radius; //maksymalny i minimalny promien kola wykrywanego przez HughCircle 
	int colorRatio[6];
	int lowThresh, upThresh;

public:
	

	Target();
	void setMinMaxRadius(int min, int max);
	void setRadiusShild(int radius);
	void setLaserColorRatio(int c1, int c2, int c3, int c4, int c5, int c6);
	void setCannyThresh(int low, int up);

	Point getTargetCenter();
	Point getLaserPosition();

	void tuneLaserColorRatio(Mat imgInput);
	void tuneThreshold(Mat imgInput);

	bool DetectTarget(Mat imgInput, Mat *imgOutput);
	void findLaser(Mat imgInput, Mat *imgOutput);


	
	~Target();
};

