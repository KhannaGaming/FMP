#include "Camera.h"



Camera::Camera()
{
	
}


Camera::~Camera()
{
	m_Camera.release();
}

int Camera::Init()
{
	if (m_Camera.open(0))
		return 0;
	else
		return -1;
}

Mat Camera::GetCameraFrame()
{
	Mat frame;
	if (m_Camera.read(frame))
	{
		return frame;
	}
	else
	{
		cout << "Either end of file or Camera has been unplugged/switched off" << endl;
		return frame;
	}
}
