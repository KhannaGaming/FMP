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
	void ApplyGreyScale(UMat* inputMatrix);
	void ApplyGaussianBlur(UMat* inputMatrix, Size kernalSize, double sigmaX);
	void ApplyGaussianBlur(UMat* inputMatrix, Size kernalSize, double sigmaX, double sigmaY, int borderType);
	void ApplyErosion(UMat* inputMatrix, int kernalType, int kernalSize);
	void ApplyDilation(UMat* inputMatrix, int kernalType, int kernalSize);
	void ConvertBGRToHSV(UMat* inputMatrix);
	vector<UMat> BuildPyramid(UMat* inputMatrix, int maxLevel, int borderType = BORDER_DEFAULT);
	void EliminateBrightLight(UMat* inputMatrix, bool trackBar = false, string winName = "");
	void GammaCorrection(UMat* inputMatrix, bool trackBar = false, string winName = "");

private:
	//************************************************
	//VARIABELS
	///<summary> Gamma slider for trackbar.
	///<para> Currently set to 17 being the most optimal.</para>
	///</summary>
	int m_gammaSlider = 17;
	
	///<summary> Bright Light slider for trackbar.
	///<para> Currently set to 93 being the most optimal.</para>
	///</summary>
	int m_saturationSlider = 93;
};

