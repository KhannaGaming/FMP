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
		return 1;
	}

	while (!m_Camera.isOpened())
	{
		int msgboxID = MessageBox(NULL,
			(LPCSTR)"Camera can not be found.\nDo you want to try again?",
			(LPCSTR)"Error message",
			MB_ICONWARNING | MB_RETRYCANCEL | MB_DEFBUTTON2);

		switch (msgboxID)
		{
		case IDCANCEL:
			return 0;
			break;
		case IDRETRY:
			if (m_Camera.open(0))
			{
				m_CameraWidth = (float)m_Camera.get(CAP_PROP_FRAME_WIDTH);
				m_CameraHeight = (float)m_Camera.get(CAP_PROP_FRAME_HEIGHT);
				return 1;
			}
			break;
		}
	}
	return 0;
}

void Camera::GetCameraFrame(UMat* currentFrame)
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
