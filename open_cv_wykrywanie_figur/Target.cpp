#include "Target.h"



Target::Target()
{
	r_shild = 120;
	lowerb = 166;
	upperb = 190;
	min_radius = 0;
	max_radius = 0;
	colorRatio[0] = 143;
	colorRatio[1] = 179;
	colorRatio[2] = 10;
	colorRatio[3] = 159;
	colorRatio[4] = 176;
	colorRatio[5] = 255;
	lowThresh = 40;
	upThresh = 120;
}


Target::~Target()
{
}
void Target::setRadiusShild(int radius)
{
	r_shild = radius;
}
void Target::setLaserColorRatio(int lower, int upper)
{
	lowerb = lower;
	upperb = upper;
}
void Target::tuneLaserColorRatio(Mat imgInput)
{
	//Mat hsv_img, binary, cont, imgCopy;
	//imgCopy = imgInput;
	//vector<Mat> hsv_split;
	//namedWindow("kolory", CV_WINDOW_AUTOSIZE);
	///*int lowerb = 100, upperb = 109; 166 190*/
	//createTrackbar("lb", "kolory", &lowerb, 255, NULL);
	//createTrackbar("ub", "kolory", &upperb, 255, NULL);
	//cvtColor(imgCopy, hsv_img, CV_BGR2HSV);
	//split(hsv_img, hsv_split);
	//while (waitKey(20) != 27)
	//{
	//inRange(hsv_split[0], lowerb, upperb, binary);

	//imshow("kolory", binary);
	//}

	namedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called "Control"

	int iLowH = colorRatio[0];
	int iHighH = colorRatio[1];

	int iLowS = colorRatio[2];
	int iHighS = colorRatio[3];

	int iLowV = colorRatio[4];
	int iHighV = colorRatio[5];

	//Create trackbars in "Control" window
	cvCreateTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
	cvCreateTrackbar("HighH", "Control", &iHighH, 179);

	cvCreateTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
	cvCreateTrackbar("HighS", "Control", &iHighS, 255);

	cvCreateTrackbar("LowV", "Control", &iLowV, 255); //Value (0 - 255)
	cvCreateTrackbar("HighV", "Control", &iHighV, 255);

	while (true)
	{
		Mat imgOriginal = imgInput;

		

		Mat imgHSV;

		cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV

		Mat imgThresholded;

		inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image

																									  //morphological opening (remove small objects from the foreground)
		erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

		//morphological closing (fill small holes in the foreground)
		dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

		imshow("Thresholded Image", imgThresholded); //show the thresholded image
		imshow("Original", imgOriginal); //show the original image

		if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
		{
			cout << "esc key is pressed by user" << endl;
			break;
		}
	}



}
void Target::setMinMaxRadius(int min, int max)
{
	min_radius = min;
	max_radius = max;
}

void Target::tuneThreshold(Mat imgInput)
{
	Mat src_gray, src = imgInput, detected_edges,dst;

	namedWindow("Control", CV_WINDOW_AUTOSIZE);
	int lowThreshold = 30;
	int upThreshold = 100;
	cvCreateTrackbar("LowThreshold", "Control", &lowThreshold, 255);
	cvCreateTrackbar("UppThreshold", "Control", &upThreshold, 1000);
	cvtColor(src, src_gray, CV_BGR2GRAY);

	while (waitKey(30) != 27)
	{
		blur(src_gray, detected_edges, Size(3, 3));
		Canny(detected_edges, detected_edges, lowThreshold, upThreshold, 3);
		dst = Scalar::all(0);
		//
		src.copyTo(dst, detected_edges);
		imshow("Control", dst);
	}
}
void Target::setCannyThresh(int low, int up)
{
	lowThresh = low;
	upThresh = up;
}
bool Target::DetectTarget(Mat imgInput, Mat *imgOutput)
{
	Mat inputCopy, src_gray, src = imgInput, potential_target;
	bool detected_circle = false;
	
	(imgInput).copyTo(inputCopy);

	/// Convert it to gray
	cvtColor(src, src_gray, CV_BGR2GRAY);
	/// Reduce the noise so we avoid false circle detection
	GaussianBlur(src_gray, src_gray, Size(9, 9), 2, 2);

	vector<Vec3f> circles;
	
	/// Apply the Hough Transform to find the circles


	HoughCircles(src_gray, circles, CV_HOUGH_GRADIENT, 1, src_gray.rows / 8, lowThresh, upThresh, min_radius, max_radius);
	
	/// Draw the circles detected
	for (size_t i = 0; i < circles.size(); i++)
	{
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		// circle center
		circle(src, center, 3, Scalar(0, 255, 0), -1, 8, 0);
		// circle outline
		circle(src, center, radius, Scalar(0, 0, 255), 3, 8, 0);
		
		//ostringstream ss;
		//ss << radius;
		//string s = ss.str();
		//putText(inputCopy, s, Point(100, 150), CV_FONT_HERSHEY_COMPLEX, 1, Scalar(20, 40, 80), 3, 8);
		try
		{
			potential_target = inputCopy(Rect(abs(center.x - r_shild), abs(center.y - r_shild), r_shild * 2, r_shild * 2));
			detected_circle = true;
			targetCenter = center;
		}
		catch(...)
		{
			detected_circle = false;
		}
		//Mat result(1, 1, CV_64F);
		//Mat lol2 = imread("lol.jpg");
		//matchTemplate(potential_target, lol2, result, CV_TM_CCOEFF_NORMED);
		//float corr_ratio = result.at<float>(0, 0);
		//cout << looo;//result.at<double>(0, 0);
		
		//string s = "r= ";// +radius;
		
		//lol = src_c(Rect(center.x - r_shild, center.y - r_shild, r_shild * 2, r_shild * 2));
	}
	//lol.create(Size(200, 200),CV_8U);

	if (detected_circle)
	{
		*imgOutput = potential_target;
		target = potential_target;
		return true;
	}
	else
	{
		detected_circle = false;
		return false;
	}
	/// Show your results
	//namedWindow("Hough Circle Transform Demo", CV_WINDOW_AUTOSIZE);
	//imshow("Hough Circle Transform Demo", lol);

}

void Target::findLaser(Mat imgInput, Mat *imgOutput)
{
	Mat hsv_img, binary, cont, imgCopy;
	imgCopy = imgInput;
	
	cvtColor(imgCopy, hsv_img, CV_BGR2HSV);

	Mat imgThresholded;
	int iLowH = colorRatio[0];
	int iHighH = colorRatio[1];

	int iLowS = colorRatio[2];
	int iHighS = colorRatio[3];

	int iLowV = colorRatio[4];
	int iHighV = colorRatio[5];
	inRange(hsv_img, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image

																								  //morphological opening (remove small objects from the foreground)
	erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
	dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

	//morphological closing (fill small holes in the foreground)
	dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
	erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

	binary = imgThresholded;
	vector<vector<Point>> contours;
	vector<Point> contours_poly;
	Rect boundRect;
	binary.copyTo(cont);
	findContours(cont, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
	int max = 0, i_cont = -1;
	Mat drawing = Mat::zeros(cont.size(), CV_8UC3);
	for (int i = 0; i< contours.size(); i++)
	{
		if (abs(contourArea(Mat(contours[i]))) > max)
		{
			max = abs(contourArea(Mat(contours[i])));
			i_cont = i;
		}
	}
	if (i_cont >= 0)
	{
		approxPolyDP(Mat(contours[i_cont]), contours_poly, 3, true);
		boundRect = boundingRect(Mat(contours_poly));
		fillConvexPoly(imgCopy, contours_poly, contours_poly.size());
		rectangle(imgCopy, boundRect.tl(), boundRect.br(), Scalar(125, 250, 125), 2, 8, 0);
		line(imgCopy, boundRect.tl(), boundRect.br(), Scalar(250, 125, 125), 2, 8, 0);
		line(imgCopy, Point(boundRect.x + boundRect.width, boundRect.y), Point(boundRect.x, boundRect.y + boundRect.height), Scalar(250, 125, 125), 2, 8, 0);
		string s;
		stringstream out;
		out << boundRect.x + boundRect.width / 2 << "x" << boundRect.y + boundRect.height / 2;
		Point contour_center;
		contour_center.x = boundRect.x + boundRect.width / 2;
		contour_center.y = boundRect.y + boundRect.height / 2;
		laser = contour_center;
		s = out.str();
		putText(imgCopy, s, Point(50, 50), CV_FONT_HERSHEY_COMPLEX, 1, Scalar(20, 40, 80), 3, 8);
		drawContours(drawing, contours, i_cont, Scalar(125, 125, 250), 2);
	}
	*imgOutput = imgCopy;
	//imshow("kolory", binary);
	
}