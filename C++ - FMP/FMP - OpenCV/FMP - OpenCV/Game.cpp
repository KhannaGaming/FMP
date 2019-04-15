#include "Game.h"

Game::Game()
{
	ocl::setUseOpenCL(true);
	faceDetection = new FaceDetection();
	m_pCamera = new Camera();
	m_pFilterFactory = new FilterFactory();
}

Game::~Game()
{
}

void Game::Run()
{
	if (Init() == 0)
		m_hasEnded = true;

	while (!m_hasEnded)
	{
		GetUserInput();
		Update();
		Render();
	}
}

void Game::Release()
{
	if (m_pCurrentFrame)
	{
		m_pCurrentFrame->release();
		delete m_pCurrentFrame;
		m_pCurrentFrame = nullptr;
	}

	delete m_pFilterFactory;
	m_pFilterFactory = nullptr;

	delete m_pCamera;
	m_pCamera = nullptr;

	delete faceDetection;
	faceDetection = nullptr;
}

int Game::Init()
{
	if (m_pCamera->Init() == 0)
		return 0;
	m_pCurrentFrame = new UMat();
	return 1;
}

void Game::GetUserInput()
{
	// Press ESC on keyboard to exit
	char key = (char)waitKey(25);
	if (key == m_escapeKey)
		m_hasEnded = true;

	//Retrieve Camera frame
	m_pCamera->GetCameraFrame(m_pCurrentFrame);
}

void Game::Update()
{
	//Apply Filters
	m_pFilterFactory->ApplyGreyScale(m_pCurrentFrame);
	m_pFilterFactory->EliminateBrightLight(m_pCurrentFrame, true, WIN_NAME);
	equalizeHist(*m_pCurrentFrame, *m_pCurrentFrame);
	m_pFilterFactory->GammaCorrection(m_pCurrentFrame,true, WIN_NAME);
	m_pFilterFactory->ApplyDilation(m_pCurrentFrame, MORPH_ELLIPSE, 2);

	//Apply Face Detection Algorithm
	faceDetection->DetectFace(m_pCurrentFrame);
	faceDetection->DetectEyes(m_pCurrentFrame);
	faceDetection->DisplayDetectedFeatures(m_pCurrentFrame);
}

void Game::Render()
{
	//Present results
	imshow(WIN_NAME, *m_pCurrentFrame);
}
