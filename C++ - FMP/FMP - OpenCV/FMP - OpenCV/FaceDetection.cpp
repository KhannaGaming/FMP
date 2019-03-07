#include "FaceDetection.h"


FaceDetection::FaceDetection()
{
	m_sigma = 3;
	m_kernalSize = (m_sigma * 5) | 1;
	face_cascade.load("D:/GitHub/FMP/C++ - FMP/opencv/build/etc/haarcascades/haarcascade_frontalface_alt2.xml");
	eye_cascade.load("D:/GitHub/FMP/C++ - FMP/opencv/build/etc/haarcascades/haarcascade_eye_tree_eyeglasses.xml");
}


FaceDetection::~FaceDetection()
{
	delete m_pCamera;
	m_pCamera = nullptr;

	delete m_pFilterFactory;
	m_pFilterFactory = nullptr;
}

int FaceDetection::Run()
{
	m_pCamera = new Camera();
	m_cameraState = m_pCamera->Init();

	m_pFilterFactory = new FilterFactory();

	while (m_cameraState == 0)
	{
		Mat currentFrame = m_pCamera->GetCameraFrame();
		//currentFrame = m_pFilterFactory->ApplyGreyScale(currentFrame);
		DetectFace(currentFrame);
		DetectEyes(currentFrame);
		DisplayDetecedFeatures(currentFrame);
		//currentFrame = m_pFilterFactory->ApplyGaussianBlur(currentFrame, Size(m_kernalSize, m_kernalSize), 2);
		imshow("Camera", currentFrame);

		// Press ESC on keyboard to exit
		char key = (char)waitKey(25);
		if (key == 27)
			m_cameraState = -1;
	}

	return 0;
}

void FaceDetection::DetectFace(Mat inputMatrix)
{
	face_cascade.detectMultiScale(inputMatrix, m_vFaces, 1.1, 2, 0, Size(140, 140));
}

void FaceDetection::DetectEyes(Mat inputMatrix)
{
	eye_cascade.detectMultiScale(inputMatrix, m_vEyes, 1.1, 10, 0, Size(30, 30));
}

void FaceDetection::DisplayDetecedFeatures(Mat inputMatrix)
{
	for (size_t i = 0; i < m_vFaces.size(); i++)
	{
		// Find the centre point of each face
		Point centre(m_vFaces[i].x + (m_vFaces[i].width*0.5), m_vFaces[i].y + (m_vFaces[i].height*0.5));
		
		// Draw a circle around each face
		ellipse(inputMatrix, centre, Size(m_vFaces[i].width*0.5, m_vFaces[i].height*0.5), 0, 0, 360, Scalar(255, 0, 255), 4, 8, 0);
	}
	for (size_t i = 0; i < m_vEyes.size(); i++)
	{
		// Find the centre point of each eye
		Point centre(m_vEyes[i].x + (m_vEyes[i].width*0.5), m_vEyes[i].y + (m_vEyes[i].height*0.5));

		// Draw a circle around each face
		ellipse(inputMatrix, centre, Size(m_vEyes[i].width*0.5, m_vEyes[i].height*0.5), 0, 0, 360, Scalar(255, 0, 255), 4, 8, 0);

	}
}
