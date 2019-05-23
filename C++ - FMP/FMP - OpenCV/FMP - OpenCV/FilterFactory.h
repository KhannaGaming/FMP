#pragma once
#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>
#include "UserInterface.h"
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
	///<summary> Apply grey scale
	///<para> inputMatrix = the input image</para>
	///</summary>
	void ApplyGreyScale(UMat* inputMatrix);

	///<summary> Apply Gaussian Blur
	///<para> inputMatrix = the input image</para>
	///<para> kernalSize = The size of the kernal</para>
	///<para> sigmaX = Gaussian kernel standard deviation in X direction.</para>
	///</summary>
	void ApplyGaussianBlur(UMat* inputMatrix, Size kernalSize, double sigmaX);

	///<summary> Apply Gausian Blur with a border type
	///<para> inputMatrix = the input image</para>
	///<para> kernalSize = The size of the kernal</para>
	///<para> sigmaX = Gaussian kernel standard deviation in X direction.</para>
	///<para> sigmaY = Gaussian kernel standard deviation in Y direction.</para>
	///<para> borderType = pixel extrapolation method.</para>
	///</summary>
	void ApplyGaussianBlur(UMat* inputMatrix, Size kernalSize, double sigmaX, double sigmaY, int borderType);

	///<summary> Apply Erosion
	///<para> inputMatrix = the input image</para>
	///<para> kernalType = The type of kernal.</para>
	///<para> kernalSize = The size of the kernal</para>
	///</summary>
	void ApplyErosion(UMat* inputMatrix, int kernalType, int kernalSize);

	///<summary> Apply Dilation
	///<para> inputMatrix = the input image</para>
	///<para> kernalType = The type of kernal.</para>
	///<para> kernalSize = The size of the kernal</para>
	///</summary>
	void ApplyDilation(UMat* inputMatrix, int kernalType, int kernalSize);

	///<summary> Convert input image from a BGR to a HSV
	///<para> inputMatrix = the input image</para>
	///</summary>
	void ConvertBGRToHSV(UMat* inputMatrix);

	///<summary> Build a Gaussian Pyramid
	///<para> inputMatrix = the input image</para>
	///<para> maxLevel = The maximum levels to the pyramid.</para>
	///<para> borderType = pixel extrapolation method</para>
	///</summary>
	vector<UMat> BuildPyramid(UMat* inputMatrix, int maxLevel, int borderType = BORDER_DEFAULT);

	///<summary> Eliminate any bright lights in the background
	///<para> inputMatrix = the input image</para>
	///<para> trackBar = Add an adjustable trackbar to test different settings.</para>
	///<para> winName = Name of the window</para>
	///</summary>
	void EliminateBrightLight(UMat* inputMatrix, bool trackBar = false, string winName = "");

	///<summary> Correct the gamma within an image
	///<para> inputMatrix = the input image</para>
	///<para> trackBar = Add an adjustable trackbar to test different settings.</para>
	///<para> winName = Name of the window</para>
	///</summary>
	void GammaCorrection(UMat* inputMatrix, bool trackBar = false, string winName = "");

private:
	//************************************************
	//POINTERS

	//************************************************
	//VARIABELS
	///<summary> Gamma slider for trackbar.
	///<para> Currently set to 8 being the most optimal.</para>
	///</summary>
	int m_gammaSlider = 8;
	
	///<summary> Bright Light slider for trackbar.
	///<para> Currently set to 93 being the most optimal.</para>
	///</summary>
	int m_saturationSlider = 230;
};

