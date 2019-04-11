#include "FaceDetection.h"
#define WIN_NAME "Camera"
#define ESCAPE_KEY 27
#define GAMMA_MAX 20
#include <thread>
#define SCALE_MAX 20
#define neighbour_MAX 60


void task1(UMat* m_pCurrentFrame)
{
		imshow(WIN_NAME, *m_pCurrentFrame);
	
}

FaceDetection::FaceDetection()
{
	m_sigma = 3;
	m_kernalSize = (m_sigma * 5) | 1;
	face_cascade= cv::makePtr<cv::CascadeClassifier>("../../opencv/build/etc/haarcascades/haarcascade_frontalface_alt2.xml");
	eye_cascade= cv::makePtr<cv::CascadeClassifier>("../../opencv/build/etc/haarcascades/haarcascade_eye.xml");
}


FaceDetection::~FaceDetection()
{
	m_pCurrentFrame->release();
	delete m_pCurrentFrame;
	m_pCurrentFrame = nullptr;

	delete m_pFilterFactory;
	m_pFilterFactory = nullptr;

	delete m_pCamera;
	m_pCamera = nullptr;

	delete eye_cascade;
	eye_cascade = nullptr;
	
	delete face_cascade;
	face_cascade = nullptr;
}

int FaceDetection::Run()
{
	m_pCamera = new Camera();
	m_cameraState = m_pCamera->Init();

	m_pFilterFactory = new FilterFactory();

	m_pCurrentFrame = new UMat();
	m_pCamera->GetCameraFrame(m_pCurrentFrame);


	while (m_cameraState == 0)
	{
		//Retrieve Camera frame
		m_pCamera->GetCameraFrame(m_pCurrentFrame);

		//Apply Filters
		m_pFilterFactory->ApplyGreyScale(m_pCurrentFrame);
		m_pFilterFactory->EliminateBrightLight(m_pCurrentFrame, true, WIN_NAME);		
		/*m_pFilterFactory->ApplyGaussianBlur(m_pCurrentFrame, Size(m_kernalSize, m_kernalSize), 1);
		m_pFilterFactory->GammaCorrection(m_pCurrentFrame, true, WIN_NAME);*/
		equalizeHist(*m_pCurrentFrame, *m_pCurrentFrame);
			//Apply Face Detection Algorithm

			DetectFace(m_pCurrentFrame);
	
			DetectEyes(m_pCurrentFrame);
			DisplayDetectedFeatures(m_pCurrentFrame);

		//Present results
		imshow(WIN_NAME, *m_pCurrentFrame);

		// Press ESC on keyboard to exit
		char key = (char)waitKey(25);
		if (key == ESCAPE_KEY)
			m_cameraState = -1;
	}

	return 0;
}

void FaceDetection::DetectFace(UMat* inputMatrix)
{

	face_cascade->detectMultiScale(*inputMatrix, m_vFaces, 1.1, 2, 0, Size(30, 30));
}

void FaceDetection::DetectEyes(UMat* inputMatrix)
{
	createTrackbar("scaleFactor", WIN_NAME, &m_scaleSlider, SCALE_MAX);
	createTrackbar("neighbours", WIN_NAME, &neibourcount, neighbour_MAX);
	float temp = m_scaleSlider / 10.0f;
	eye_cascade->detectMultiScale(*inputMatrix, m_vEyes, temp, neibourcount, 0, Size(30, 30));
}

void FaceDetection::DisplayDetectedFeatures(UMat* inputMatrix)
{
	for (size_t i = 0; i < m_vFaces.size(); i++)
	{
		// Find the centre point of each face
		Point centre(m_vFaces[i].x + (m_vFaces[i].width*0.5f), m_vFaces[i].y + (m_vFaces[i].height*0.5f));

		// Draw a circle around each face
		ellipse(*inputMatrix, centre, Size(m_vFaces[i].width*0.5, m_vFaces[i].height*0.5), 0, 0, 360, Scalar(255, 0, 255), 4, 8, 0);
		for (size_t i = 0; i < m_vEyes.size(); i++)
		{
			// Find the centre point of each eye
			Point centre(m_vEyes[i].x + (m_vEyes[i].width*0.5), m_vEyes[i].y + (m_vEyes[i].height*0.5));

			// Draw a circle around each face
			ellipse(*inputMatrix, centre, Size(m_vEyes[i].width*0.5, m_vEyes[i].height*0.5), 0, 0, 360, Scalar(255, 0, 255), 4, 8, 0);
		}		
	}
}



