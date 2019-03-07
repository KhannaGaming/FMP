#pragma once
#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>

using namespace cv;
using namespace std;

class FilterFactory
{
public:
	FilterFactory();
	~FilterFactory();

	Mat ApplyGreyScale(Mat inputMatrix);
	Mat ApplyGaussianBlur(Mat inputMatrix, Size kernalSize, double sigmaX);
	Mat ApplyGaussianBlur(Mat inputMatrix, Size kernalSize, double sigmaX, double sigmaY, int borderType);
	Mat ApplyErosion(Mat inputMatrix, int kernalType, int kernalSize);
	Mat ApplyDilation(Mat inputMatrix, int kernalType, int kernalSize);
};

