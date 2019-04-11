#include "FaceDetection.h"

int main()
{
	ocl::setUseOpenCL(true);

	FaceDetection* faceDetection = new FaceDetection();
	faceDetection->Run();

	delete faceDetection;
	faceDetection = nullptr;

	return 0;
}