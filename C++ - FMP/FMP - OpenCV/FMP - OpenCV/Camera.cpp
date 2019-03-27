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
	{
		m_CameraWidth = (float)m_Camera.get(CAP_PROP_FRAME_WIDTH);
		m_CameraHeight = (float)m_Camera.get(CAP_PROP_FRAME_HEIGHT);
		return 0;
	}
	else
		return -1;
}

void Camera::GetCameraFrame(Mat* currentFrame)
{
	if (!m_Camera.read(*currentFrame))
	{
		cout << "Either end of file or Camera has been unplugged/switched off" << endl;		
	}
}

float Camera::GetCameraWidth()
{
	return m_CameraWidth;
}

float Camera::GetCameraHeight()
{
	return m_CameraHeight;
}
