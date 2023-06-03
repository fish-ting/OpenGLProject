#pragma once

#include "Base.h"

class Shader
{
private:
	unsigned int m_shaderProgram;

public:
	Shader()
	{
		m_shaderProgram = 0;
	}

	~Shader()
	{

	}

	void initShader(const char* _vertexPath, const char* _fragmentPath);

	void start()
	{
		glUseProgram(m_shaderProgram);
	}

	void end()
	{
		glUseProgram(0);
	}

	// 封装函数：向shader里传输数据
	void setMatrix(const std::string& _name, glm::mat4 _matrix)const;
};

