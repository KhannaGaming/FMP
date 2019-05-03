#include "UserInterface.h"



UserInterface::UserInterface()
{
}


UserInterface::~UserInterface()
{
}

void UserInterface::CreateTrackbar(string name, string windowName, int* value, int maxValue)
{
	createTrackbar(name, windowName, value, maxValue);
}

void UserInterface::CreateOnScreenText(UMat* img, string text, Point2f location)
{
	putText(*img, text, location, FONT_HERSHEY_PLAIN, 2, Scalar(255, 0, 0), 2, 8, false);
}
