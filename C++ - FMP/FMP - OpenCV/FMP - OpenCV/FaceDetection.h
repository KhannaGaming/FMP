#pragma once
#include "Camera.h"
#include "FilterFactory.h"
#include "opencv2/core/cuda_types.hpp"
#include "opencv2/core/cuda.inl.hpp"
#include <opencv2/core/ocl.hpp>
static string WIN_NAME = "Camera";

class FaceDetection
{
public:
	//************************************************
	//VARIABELS
	int m_leftEyeWinkCount = 0;
	int m_rightEyeWinkCount = 0;

	//************************************************
	//METHODS
	FaceDetection();
	~FaceDetection();
	void DetectFace(UMat* inputMatrix);
	void DetectEyes(UMat* inputMatrix);
	void DisplayDetectedFeatures(UMat* inputMatrix);

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
	int m_scaleSlider = 11;
	int neibourcount = 8;
	int detectionSize = 10;
};

