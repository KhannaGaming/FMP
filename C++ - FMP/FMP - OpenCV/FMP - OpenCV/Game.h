#pragma once
#include "FaceDetection.h"
#include "Camera.h"

class Game
{
public:
	Game();
	~Game();
	void Run();
	void Release();

private:
	//************************************************
	//POINTERS
	FaceDetection * faceDetection;
	Camera * m_pCamera;
	FilterFactory* m_pFilterFactory;
	UMat* m_pCurrentFrame;
	UserInterface* m_pUI;

	//************************************************
	//VARIABELS
	bool m_hasEnded = false;
	int m_escapeKey = 27;

	//************************************************
	//METHODS
	int Init();
	void GetUserInput();
	void Update();
	void Render();
};

