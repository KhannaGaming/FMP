#pragma once
#include "Camera.h"
#include "FilterFactory.h"
#include "opencv2/core/cuda_types.hpp"
#include "opencv2/core/cuda.inl.hpp"
#include <opencv2/core/ocl.hpp>
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
	UMat* m_pCurrentFrame;
	//************************************************
	//VARIABELS
	int m_cameraState = 0;
	int m_sigma = 0;
	int m_kernalSize = 0;
	vector <Rect> m_vFaces;
	vector <Rect> m_vEyes;
	Ptr<CascadeClassifier> face_cascade;
	Ptr<CascadeClassifier> eye_cascade;
	int m_scaleSlider = 12;
	int neibourcount = 20;
	//************************************************
	//METHODS
	void DetectFace(UMat* inputMatrix);
	void DetectEyes(UMat* inputMatrix);
	void DisplayDetectedFeatures(UMat* inputMatrix);
};

