#pragma once
#include <windows.h>
#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>
using namespace cv;
using namespace std;

class Camera
{
public:
	Camera();
	~Camera();
		
	int Init();

	///<summary> Detect Eyes
	///<para> currentFrame = A matrix to allow an image from the camera to be saved to</para>
	///</summary>
	void GetCameraFrame(UMat* currentFrame);
	float GetCameraWidth();
	float GetCameraHeight();

private:

	VideoCapture m_Camera;
	float m_CameraWidth;
	float m_CameraHeight;
};

