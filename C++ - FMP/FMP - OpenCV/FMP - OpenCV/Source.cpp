#include "FaceDetection.h"

int main()
{
	FaceDetection* faceDetection = new FaceDetection();
	faceDetection->Run();

	delete faceDetection;
	faceDetection = nullptr;

	return 0;
}