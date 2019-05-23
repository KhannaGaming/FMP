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
	bool m_LeftEyeClosed = false;
	bool m_RightEyeClosed = false;
	int m_scaleSlider = 11;
	int m_faceNeighbourCount = 2;
	int m_eyeNeighbourCount = 10;
	int m_eyeDetectionSize = 14;
	int m_faceDetectionSize = 30;
	const int m_maxiumFaceScale = 20;
	const int m_maxiumEyeDetectionSize = 100;
	const int m_maximumNeighbours = 60;

	//************************************************
	//METHODS
	FaceDetection();
	~FaceDetection();

	///<summary> Detect Face
	///<para> inputMatrix = the input image</para>
	///</summary>
	void DetectFace(UMat* inputMatrix);

	///<summary> Detect Eyes
	///<para> inputMatrix = the input image</para>
	///</summary>
	void DetectEyes(UMat* inputMatrix);

	///<summary> Display any detected features
	///<para> inputMatrix = the input image</para>
	///</summary>
	void DisplayDetectedFeatures(UMat* inputMatrix);

private:

	//************************************************
	//VARIABELS
	int m_cameraState = 0;
	double m_faceScaleFactor = 1.1;
	int m_borderThickness = 4;
	vector <Rect> m_vFaces;
	vector <Rect> m_vEyes;
	CascadeClassifier m_faceCascade;
	CascadeClassifier m_eyeCascade;
	UserInterface m_pUI;
	Scalar m_Red = Scalar(255, 0, 0);
};

