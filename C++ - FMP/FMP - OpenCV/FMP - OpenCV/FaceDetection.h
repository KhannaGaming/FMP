#pragma once
#include "Camera.h"
#include "FilterFactory.h"

class FaceDetection
{
public:
	//************************************************
	//METHODS
	FaceDetection();
	~FaceDetection();

	int Run();

private:
	//************************************************
	//POINTERS
	Camera * m_pCamera;
	FilterFactory* m_pFilterFactory;
	Mat* m_pCurrentFrame;
	//************************************************
	//VARIABELS
	int m_cameraState = 0;
	int m_sigma = 0;
	int m_kernalSize = 0;
	vector <Rect> m_vFaces;
	vector <Rect> m_vEyes;
	CascadeClassifier face_cascade;
	CascadeClassifier eye_cascade;

	//************************************************
	//METHODS
	void DetectFace(Mat* inputMatrix);
	void DetectEyes(Mat* inputMatrix);
	void DisplayDetectedFeatures(Mat* inputMatrix);
};

