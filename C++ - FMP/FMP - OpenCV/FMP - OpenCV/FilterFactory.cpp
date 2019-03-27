#include "FilterFactory.h"


FilterFactory::FilterFactory()
{
}


FilterFactory::~FilterFactory()
{
}

void FilterFactory::ApplyGreyScale(Mat* inputMatrix)
{
	cvtColor(*inputMatrix, *inputMatrix, COLOR_BGR2GRAY);
}

void FilterFactory::ApplyGaussianBlur(Mat* inputMatrix, Size kernalSize, double sigmaX)
{
	GaussianBlur(*inputMatrix, *inputMatrix, kernalSize, sigmaX);
}

void FilterFactory::ApplyGaussianBlur(Mat* inputMatrix, Size kernalSize, double sigmaX, double sigmaY, int borderType)
{
	GaussianBlur(*inputMatrix, *inputMatrix, kernalSize, sigmaX, sigmaY, borderType);
}

void FilterFactory::ApplyErosion(Mat* inputMatrix, int kernalType, int kernalSize)
{
	Mat element = getStructuringElement(kernalType, Size(2 * kernalSize + 1, 2 * kernalSize + 1), Point(kernalSize, kernalSize));
	erode(*inputMatrix, *inputMatrix, element);
}

void FilterFactory::ApplyDilation(Mat* inputMatrix, int kernalType, int kernalSize)
{
	Mat element = getStructuringElement(kernalType, Size(2 * kernalSize + 1, 2 * kernalSize + 1), Point(kernalSize, kernalSize));
	dilate(*inputMatrix, *inputMatrix, element);
}

void FilterFactory::ConvertBGRToHSV(Mat * inputMatrix)
{
	cvtColor(*inputMatrix, *inputMatrix, COLOR_BGR2HSV);
}

vector<Mat> FilterFactory::BuildPyramid(Mat * inputMatrix, int maxLevel, int borderType)
{
	vector<Mat> arrayOfArrays;
	buildPyramid(*inputMatrix, arrayOfArrays, maxLevel, borderType);
	return arrayOfArrays;
}

Mat* FilterFactory::EliminateBrightLight(Mat * inputMatrix, bool trackBar, string winName)
{
	if (trackBar)
		createTrackbar("Light", winName, &m_saturationSlider, SATURATION_MAX);

	Mat * mask = new Mat();
	inRange(*inputMatrix, Scalar(0, 0, 0), Scalar(m_saturationSlider, m_saturationSlider, m_saturationSlider), *mask);
	
	Mat * res = new Mat();
	bitwise_and(*inputMatrix, *inputMatrix, *res, *mask);
	return res;
}

void FilterFactory::GammaCorrection(Mat * inputMatrix, bool trackBar, string winName)
{
	if (trackBar)
		createTrackbar("Gamma", winName, &m_gammaSlider, GAMMA_MAX);
	float gamma = m_gammaSlider / 10.0f;

	unsigned char lut[256];

	for (int i = 0; i < 256; i++)
	{
		lut[i] = saturate_cast<uchar>(pow((float)(i / 255.0), gamma) * 255.0f);
	}


	const int channels = inputMatrix->channels();
	switch (channels)
	{
	case 1:
	{
		MatIterator_<uchar> it, end;
		for (it = inputMatrix->begin<uchar>(), end = inputMatrix->end<uchar>(); it != end; it++)
			*it = lut[(*it)];
		break;
	}

	case 3:
	{
		MatIterator_<Vec3b> it, end;
		for (it = inputMatrix->begin<Vec3b>(), end = inputMatrix->end<Vec3b>(); it != end; it++)
		{
			(*it)[0] = lut[((*it)[0])];
			(*it)[1] = lut[((*it)[1])];
			(*it)[2] = lut[((*it)[2])];
		}
		break;
	}
	}

}
