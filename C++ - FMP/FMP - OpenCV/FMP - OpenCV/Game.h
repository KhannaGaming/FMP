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
	int m_maxSliderAmount = 11;

	//************************************************
	//METHODS
	///<summary> Initialise game.
	///</summary>
	int Init();

	///<summary> Get user input.
	///</summary>
	void GetUserInput();

	///<summary> Update the game.
	///<para> Apply filters and face detections.</para>
	///</summary>
	void Update();

	///<summary> Render results to screen.
	///</summary>
	void Render();
};

