#pragma once
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
	void GetCameraFrame(UMat* currentFrame);
	float GetCameraWidth();
	float GetCameraHeight();

private:

	VideoCapture m_Camera;
	float m_CameraWidth;
	float m_CameraHeight;
};

