#include "Camera.h"


void Camera::lookAt(glm::vec3 _pos, glm::vec3 _front, glm::vec3 _up)
{
	m_position = _pos;
	m_front = glm::normalize(_front);
	m_up = _up;

	m_vMatrix = glm::lookAt(m_position, m_position + m_front, m_up);
}

void Camera::update()
{
	// 构造照相机矩阵
	m_vMatrix = glm::lookAt(m_position, m_position + m_front, m_up);
}

glm::mat4 Camera::getMatrix()
{
	return m_vMatrix;
}

void Camera::move(CAMERA_MOVE _mode)
{
	switch (_mode)
	{
	case CAMERA_MOVE::MOVE_LEFT:
		m_position -= glm::normalize(glm::cross(m_front, m_up)) * m_speed;
		break;
	case CAMERA_MOVE::MOVE_RIGHT:
		m_position += glm::normalize(glm::cross(m_front, m_up)) * m_speed;
		break;
	case CAMERA_MOVE::MOVE_FRONT:
		m_position += m_speed * m_front;
		break;
	case CAMERA_MOVE::MOVE_BACK:
		m_position -= m_speed * m_front;
		break;
	default:
		break;
	}
}