#pragma once
#include "Camera.h"
#include "FilterFactory.h"
#include "UserInterface.h"
static string WIN_NAME = "Camera";

class FaceDetection
{
public:
	//************************************************
	//VARIABELS
	int m_leftEyeWinkCount = 0;
	int m_rightEyeWinkCount = 0;
	int m_scaleSlider = 11;
	int neibourcount = 5;
	int detectionSize = 10;
	const int SCALE_MAX  = 20;
	const int neighbour_MAX = 60;

	//************************************************
	//METHODS
	FaceDetection();
	~FaceDetection();
	void DetectFace(UMat* inputMatrix);
	void DetectEyes(UMat* inputMatrix);
	void DisplayDetectedFeatures(UMat* inputMatrix);
	void CreateTrackbars();

private:
	
	//************************************************
	//VARIABELS
	int m_cameraState = 0;
	int m_sigma = 0;
	int m_kernalSize = 0;
	vector <Rect> m_vFaces;
	vector <Rect> m_vEyes;
	CascadeClassifier face_cascade;
	CascadeClassifier eye_cascade;
	UserInterface m_pUI;
	Scalar Red = Scalar(255, 0, 0);
};

