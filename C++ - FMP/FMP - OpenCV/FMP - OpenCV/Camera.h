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
	Mat GetCameraFrame();
private:
	VideoCapture m_Camera;
};

