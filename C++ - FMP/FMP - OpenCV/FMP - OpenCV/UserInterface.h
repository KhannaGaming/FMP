#pragma once
#include <opencv2/opencv.hpp>
#include "opencv2/core/cuda_types.hpp"
#include "opencv2/core/cuda.inl.hpp"
#include <opencv2/core/ocl.hpp>
#include <string>
using namespace std;
using namespace cv;
class UserInterface
{
public:
	UserInterface();
	~UserInterface();

	//************************************************
	//METHODS
	///<summary> Create a trackbar based on parameters
	///<para> name = Name to be displayed</para>
	///<para> windowName = The window name</para>
	///<para> value = Value that will be changed</para>
	///<para> maxValue = The maximum value that value can be</para>
	///</summary>
	void CreateTrackbar(string name, string windowName, int* value, int maxValue);

	///<summary> Create text on screen in a set location
	///<para> img = The image to draw to</para>
	///<para> text = The text to show</para>
	///<para> location = The location in which to draw from</para>
	///</summary>
	void CreateOnScreenText(UMat* img, string text, Point2f location);
private: 

	//************************************************
	//VARIABELS
	Scalar m_Red = Scalar(255, 0, 0);
	int m_lineThickness = 2;
	int m_fontSize = 2;
};

