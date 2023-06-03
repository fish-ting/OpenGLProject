#pragma once
#include <glad/glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

typedef unsigned int  uint;
typedef unsigned char byte;

// ��ɫ
struct  ffRGBA
{
	byte m_b;
	byte m_g;
	byte m_r;
	byte m_a;

	ffRGBA(byte _r = 255, byte _g = 255, byte _b = 255, byte _a = 255)
	{
		m_r = _r;
		m_g = _g;
		m_b = _b;
		m_a = _a;
	}
};

// ģ��
template<typename T>
struct  tVec3
{
	T m_x;
	T m_y;
	T m_z;

	tVec3(T _x = 0, T _y = 0, T _z = 0)
	{
		m_x = _x;
		m_y = _y;
		m_z = _z;
	}
};

template<typename T>
struct  tVec2
{
	T m_x;
	T m_y;

	tVec2(T _x = 0, T _y = 0)
	{
		m_x = _x;
		m_y = _y;
	}
};