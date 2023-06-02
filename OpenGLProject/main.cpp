#include <glad/glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

unsigned int VAO = 0;
unsigned int VBO = 0;
unsigned int shaderProgram = 0;

void rend()
{
	glUseProgram(shaderProgram);

	float _time = glfwGetTime();
	float _green = sin(_time) * 0.5f + 0.5f;

	// 获取在shader中的位置
	int _location = glGetUniformLocation(shaderProgram, "outColor");
	// 使用 uniform 数据类型
	glUniform4f(_location, 0.0f, _green, 0.0f, 1.0f);

	glBindVertexArray(VAO);

	glDrawArrays(GL_TRIANGLES, 0, 3);
	glUseProgram(0);
}

// 告诉shader数据解析方式
// 激活锚点

void initModel()
{
	float vertices[] =
	{
		-0.5f, -0.5, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};

	//获取VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// 获取vbo的index，即到底要分配多少个vbo
	glGenBuffers(1, &VBO);

	// 绑定vbo的index
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// 给vbo分配显存空间，传输数据
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// 告诉shader数据解析方式
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	// 激活锚点
	glEnableVertexAttribArray(0);

	// 取消绑定
	glBindBuffer(GL_ARRAY_BUFFER, 0); // VBO 解绑
	glBindVertexArray(0); // VAO 解绑
}

void initShader(const char* _vertexPath, const char* _fragmentPath)
{
	std::string _vertexCode("");
	std::string _fragCode("");

	// 读取文件工具
	std::ifstream _vShaderFile;
	std::ifstream _fShaderFile;

	// 检测是否有正确读入
	_vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	_fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	// 读取着色器文件
	try
	{
		_vShaderFile.open(_vertexPath);
		_fShaderFile.open(_fragmentPath);

		std::stringstream _vShaderStream, _fShaderStream;  // 读取流

		_vShaderStream << _vShaderFile.rdbuf();
		_fShaderStream << _fShaderFile.rdbuf();

		_vertexCode = _vShaderStream.str();
		_fragCode = _fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::string errStr = "read shader fail";
		std::cout << errStr << std::endl;
	}

	const char* _vShaderStr = _vertexCode.c_str();
	const char* _fShaderStr = _fragCode.c_str();

	// 着色器的编译
	unsigned int _vertexID = 0;
	unsigned int _fragID = 0;

	char _infoLog[512]; // 存储错误信息
	int _successFlag = 0;

	// 顶点着色器
	_vertexID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(_vertexID, 1, &_vShaderStr, NULL);
	glCompileShader(_vertexID);

	// 检查是否编译成功
	glGetShaderiv(_vertexID, GL_COMPILE_STATUS, &_successFlag);
	if (!_successFlag)
	{
		glGetShaderInfoLog(_vertexID, 512, NULL, _infoLog);
		std::string errStr(_infoLog);
		std::cout << _infoLog << std::endl;
	}

	// 片元着色器
	_fragID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(_fragID, 1, &_fShaderStr, NULL);
	glCompileShader(_fragID);

	// 检查是否编译成功
	glGetShaderiv(_fragID, GL_COMPILE_STATUS, &_successFlag);
	if (!_successFlag)
	{
		glGetShaderInfoLog(_fragID, 512, NULL, _infoLog);
		std::string errStr(_infoLog);
		std::cout << _infoLog << std::endl;
	}

	// 着色器的链接
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, _vertexID);
	glAttachShader(shaderProgram, _fragID);
	glLinkProgram(shaderProgram);

	// 检查是否链接成功
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &_successFlag);
	if (!_successFlag)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, _infoLog);
		std::string errStr(_infoLog);
		std::cout << _infoLog << std::endl;
	}

	glDeleteShader(_vertexID);
	glDeleteShader(_fragID);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	// 主动检测当前窗口是否被按下 ESC 按钮
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

int main()
{
	// 初始化窗口库
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}
	// 4.3 版本
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL - Render", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		exit(EXIT_FAILURE);
	}

	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // 窗口大小被改变时就会被调用

	initModel();
	initShader("vertexShader.glsl", "fragmentShader.glsl");

	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// 绘图
		rend();

		glfwSwapBuffers(window); // 交换颜色缓冲区，防止屏幕碎裂
		glfwPollEvents(); // 处理用户交互事件
	}

	glfwTerminate();
	return 0;
}