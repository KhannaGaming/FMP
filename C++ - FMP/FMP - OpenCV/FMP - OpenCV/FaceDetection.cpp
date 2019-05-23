#include "FaceDetection.h"
#define GAMMA_MAX 20
#include <thread>



FaceDetection::FaceDetection()
{
#ifdef _DEBUG
	m_faceCascade.load("lbpcascade_frontalface.xml");
	m_eyeCascade.load("haarcascade_eye_tree_eyeglasses.xml");
#else
	m_faceCascade.load("lbpcascade_frontalface.xml");
	m_eyeCascade.load("haarcascade_eye_tree_eyeglasses.xml");
#endif
}


FaceDetection::~FaceDetection()
{	
}


void FaceDetection::DetectFace(UMat* inputMatrix)
{
	m_faceCascade.detectMultiScale(*inputMatrix, m_vFaces, m_faceScaleFactor, m_faceNeighbourCount, 0, Size(m_faceDetectionSize, m_faceDetectionSize));
}

void FaceDetection::DetectEyes(UMat* inputMatrix)
{
	float temp = m_scaleSlider / 10.0f;
	m_eyeCascade.detectMultiScale(*inputMatrix, m_vEyes, temp, m_eyeNeighbourCount, 0, Size(m_eyeDetectionSize, m_eyeDetectionSize));
}

void FaceDetection::DisplayDetectedFeatures(UMat* inputMatrix)
{
	m_RightEyeClosed = false;
	m_LeftEyeClosed = false;
	for (size_t i = 0; i < m_vFaces.size(); i++)
	{
		// Find the centre point of each face
		Point centre(m_vFaces[i].x + (m_vFaces[i].width / 2), m_vFaces[i].y + (m_vFaces[i].height / 2));

		// Draw a circle around each face
		ellipse(*inputMatrix, centre, Size(m_vFaces[i].width / 2, m_vFaces[i].height / 2), 0, 0, 360, m_Red, m_borderThickness);
		for (size_t i = 0; i < m_vEyes.size(); i++)
		{
			// Find the centre point of each eye
			Point centre(m_vEyes[i].x + (m_vEyes[i].width / 2), m_vEyes[i].y + (m_vEyes[i].height / 2));

			// Draw a circle around each face
			ellipse(*inputMatrix, centre, Size(m_vEyes[i].width / 2, m_vEyes[i].height / 2), 0, 0, 360, m_Red, m_borderThickness);
		}

	}
		// Count winks
		if (m_vEyes.size() == 1 && m_vFaces.size() >= 1)
		{
			if (m_vEyes[0].x > (m_vFaces[0].x + (m_vFaces[0].width / 2)))
			{
				m_RightEyeClosed = true;
			}
			else
			{
				m_LeftEyeClosed = true;
			}
		}
}



