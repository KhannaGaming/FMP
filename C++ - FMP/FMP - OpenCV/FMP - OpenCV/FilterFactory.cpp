#include "FilterFactory.h"



FilterFactory::FilterFactory()
{
}


FilterFactory::~FilterFactory()
{
}

Mat FilterFactory::ApplyGreyScale(Mat inputMatrix)
{
	Mat outputMatrix;
	cvtColor(inputMatrix, outputMatrix, COLOR_BGRA2GRAY);
	return outputMatrix;
}

Mat FilterFactory::ApplyGaussianBlur(Mat inputMatrix, Size kernalSize, double sigmaX)
{
	Mat outputMatrix;
	GaussianBlur(inputMatrix, outputMatrix, kernalSize, sigmaX);
	return outputMatrix;
}

Mat FilterFactory::ApplyGaussianBlur(Mat inputMatrix, Size kernalSize, double sigmaX, double sigmaY, int borderType)
{
	Mat outputMatrix;
	GaussianBlur(inputMatrix, outputMatrix, kernalSize, sigmaX, sigmaY, borderType);
	return outputMatrix;
}

Mat FilterFactory::ApplyErosion(Mat inputMatrix, int kernalType, int kernalSize)
{
	Mat outputMatrix;
	Mat element = getStructuringElement(kernalType, Size(2 * kernalSize + 1, 2 * kernalSize + 1), Point(kernalSize, kernalSize));
	erode(inputMatrix, outputMatrix, element);
	return outputMatrix;
}

Mat FilterFactory::ApplyDilation(Mat inputMatrix, int kernalType, int kernalSize)
{
	Mat outputMatrix;
	Mat element = getStructuringElement(kernalType, Size(2 * kernalSize + 1, 2 * kernalSize + 1), Point(kernalSize, kernalSize));
	dilate(inputMatrix, outputMatrix, element);
	return outputMatrix;
}
