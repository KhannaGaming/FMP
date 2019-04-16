#include "FaceDetection.h"
#define GAMMA_MAX 20
#include <thread>
#define SCALE_MAX 20
#define neighbour_MAX 60


FaceDetection::FaceDetection()
{
	m_sigma = 3;
	m_kernalSize = (m_sigma * 5) | 1;
	//face_cascade.load("../../opencv/build/etc/haarcascades/haarcascade_frontalface_alt2.xml");
	face_cascade.load("../../opencv/build/etc/lbpcascades/lbpcascade_frontalface.xml");
	eye_cascade.load("../../opencv/build/etc/haarcascades/haarcascade_eye.xml");
}


FaceDetection::~FaceDetection()
{	
}


void FaceDetection::DetectFace(UMat* inputMatrix)
{
	face_cascade.detectMultiScale(*inputMatrix, m_vFaces, 1.2, 2, 0, Size(30, 30));	
}

void FaceDetection::DetectEyes(UMat* inputMatrix)
{
	createTrackbar("scaleFactor", WIN_NAME, &m_scaleSlider, SCALE_MAX);
	createTrackbar("neighbours", WIN_NAME, &neibourcount, neighbour_MAX);
	if (m_scaleSlider < 11)
		m_scaleSlider = 11;
	float temp = m_scaleSlider / 10.0f;
	eye_cascade.detectMultiScale(*inputMatrix, m_vEyes, temp, neibourcount, 0, Size(50, 50));
}

void FaceDetection::DisplayDetectedFeatures(UMat* inputMatrix)
{
	for (size_t i = 0; i < m_vFaces.size(); i++)
	{
		// Find the centre point of each face
		Point centre(m_vFaces[i].x + (m_vFaces[i].width / 2), m_vFaces[i].y + (m_vFaces[i].height / 2));

		// Draw a circle around each face
		ellipse(*inputMatrix, centre, Size(m_vFaces[i].width / 2, m_vFaces[i].height / 2), 0, 0, 360, Scalar(255, 0, 255), 4, 8, 0);
		for (size_t i = 0; i < m_vEyes.size(); i++)
		{
			// Find the centre point of each eye
			Point centre(m_vEyes[i].x + (m_vEyes[i].width / 2), m_vEyes[i].y + (m_vEyes[i].height / 2));

			// Draw a circle around each face
			ellipse(*inputMatrix, centre, Size(m_vEyes[i].width / 2, m_vEyes[i].height / 2), 0, 0, 360, Scalar(255, 0, 255), 4, 8, 0);

		}

	}
		// Count winks
		if (m_vEyes.size() == 1 && m_vFaces.size() >= 1)
		{
			if (m_vEyes[0].x > (m_vFaces[0].x + (m_vFaces[0].width / 2)))
			{
				++m_rightEyeWinkCount;
			}
			else
			{
				++m_leftEyeWinkCount;
			}
		}
}



