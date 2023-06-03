#pragma once

#include "Base.h"

enum class CAMERA_MOVE
{
	MOVE_LEFT,
	MOVE_RIGHT,
	MOVE_FRONT,
	MOVE_BACK
};

class Camera
{
private:
	glm::vec3 m_position;
	glm::vec3 m_front;
	glm::vec3 m_up;
	float     m_speed;

	glm::mat4 m_vMatrix;

public:
	Camera()
	{
		m_position = glm::vec3(1.0f);
		m_front = glm::vec3(1.0f);
		m_up = glm::vec3(1.0f);
		m_speed = 0.01f;

		m_vMatrix = glm::mat4(1.0f);

	}

	~Camera()
	{

	}

	void lookAt(glm::vec3 _pos, glm::vec3 _front, glm::vec3 _up);

	void update();

	glm::mat4 getMatrix();

	void move(CAMERA_MOVE _mode);

	void setSpeed(float _speed)
	{
		m_speed = _speed;
	}
};

