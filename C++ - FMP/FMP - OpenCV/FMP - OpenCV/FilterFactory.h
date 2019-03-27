#pragma once
#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>
#define SATURATION_MAX  255
#define GAMMA_MAX  20

using namespace cv;
using namespace std;

class FilterFactory
{
public:
	FilterFactory();
	~FilterFactory();
	//************************************************
	//METHODS
	void ApplyGreyScale(Mat* inputMatrix);
	void ApplyGaussianBlur(Mat* inputMatrix, Size kernalSize, double sigmaX);
	void ApplyGaussianBlur(Mat* inputMatrix, Size kernalSize, double sigmaX, double sigmaY, int borderType);
	void ApplyErosion(Mat* inputMatrix, int kernalType, int kernalSize);
	void ApplyDilation(Mat* inputMatrix, int kernalType, int kernalSize);
	void ConvertBGRToHSV(Mat* inputMatrix);
	vector<Mat> BuildPyramid(Mat* inputMatrix, int maxLevel, int borderType = BORDER_DEFAULT);
	Mat* EliminateBrightLight(Mat* inputMatrix, bool trackBar = false, string winName = "");
	void GammaCorrection(Mat* inputMatrix, bool trackBar = false, string winName = "");

private:
	//************************************************
	//VARIABELS
	int m_gammaSlider = GAMMA_MAX/2;
	int m_saturationSlider = SATURATION_MAX;
};

