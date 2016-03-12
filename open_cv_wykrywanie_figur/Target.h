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
	Point targetCenter, laser; //srodek wykrytej tarczy, laser
	
	int lowerb, upperb; 
	int min_radius, max_radius; //maksymalny i minimalny promien kola wykrywanego przez HughCircle 
	int colorRatio[6];
	int lowThresh, upThresh;

public:
	

	Target();
	bool DetectTarget(Mat imgInput, Mat *imgOutput);
	void findLaser(Mat imgInput, Mat *imgOutput);
	void setRadiusShild(int radius);
	void setLaserColorRatio(int lower, int upper);
	void tuneLaserColorRatio(Mat imgInput);
	void setMinMaxRadius(int min, int max);
	void tuneThreshold(Mat imgInput);
	void setCannyThresh(int low, int up);
	~Target();
};

