#include "Base.h"
#include "Shader.h"
#include "ffImage.h"
#include "Camera.h"


unsigned int VAO = 0;
unsigned int VBO = 0;

ffImage* _pImage = NULL;

unsigned int _texture = 0;

Shader _shader;

glm::mat4 _viewMatrix(1.0f);
glm::mat4 _projMatrix(1.0f);

int _width = 820;
int _height = 820;

Camera _camera;

void rend()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	// 颜色和深度区清零
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// 开启深度检测
	glEnable(GL_DEPTH_TEST);

	// 数据准备
	glm::vec3 modelVecs[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	// 计算变换矩阵
	//_viewMatrix = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0, 1, 0));
	_camera.update();
	_projMatrix = glm::perspective(glm::radians(45.0f), (float)_width / (float)_height, 0.1f, 100.0f);


	//glBindTexture(GL_TEXTURE_2D, _texture);

	// 画多个立方体

	for (int i = 0; i < 10; i++) {
		glm::mat4 _modelMatrix(1.0f);
		_modelMatrix = glm::translate(_modelMatrix, modelVecs[i]);
		_modelMatrix = glm::rotate(_modelMatrix, glm::radians((float)glfwGetTime() * (i + 1) * 10), glm::vec3(0.0f, 1.0f, 0.0f));

		_shader.start();
		_shader.setMatrix("_modelMatrix", _modelMatrix);
		_shader.setMatrix("_viewMatrix", _camera.getMatrix());
		_shader.setMatrix("_projMatrix", _projMatrix);

		glBindVertexArray(VAO);

		glDrawArrays(GL_TRIANGLES, 0, 36); // 画36个点
		_shader.end();
	}
}

// 告诉shader数据解析方式
// 激活锚点

void initModel()
{
	// 坐标 - uv , 12个三角形
	float vertices[] =
	{
		-0.5f,  -0.5,  -0.5f,    0.0f, 0.0f,
		 0.5f,  -0.5,  -0.5f,    1.0f, 0.0f,
		 0.5f,   0.5,  -0.5f,    1.0f, 1.0f,
		 0.5f,   0.5,  -0.5f,    1.0f, 1.0f,
		-0.5f,   0.5,  -0.5f,    0.0f, 1.0f,
		-0.5f,  -0.5,  -0.5f,    0.0f, 0.0f,

		-0.5f,  -0.5,   0.5f,    0.0f, 0.0f,
		 0.5f,  -0.5,   0.5f,    1.0f, 0.0f,
		 0.5f,   0.5,   0.5f,    1.0f, 1.0f,
		 0.5f,   0.5,   0.5f,    1.0f, 1.0f,
		-0.5f,   0.5,   0.5f,    0.0f, 1.0f,
		-0.5f,  -0.5,   0.5f,    0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	//获取VAO，在关闭VAO前，期间所有的数据都会被纳入VAO的管理
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// 获取vbo的index，即到底要分配多少个vbo
	glGenBuffers(1, &VBO);

	// 绑定vbo的index
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// 给vbo分配显存空间，传输数据
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// 告诉shader数据解析方式
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(sizeof(float) * 3));

	// 激活锚点
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	// 取消绑定
	glBindBuffer(GL_ARRAY_BUFFER, 0); // VBO 解绑
	glBindVertexArray(0); // VAO 解绑
}

void initTexture()
{
	_pImage = ffImage::readFromFile("res/fish.jpg");

	// 生成纹理对象并绑定
	glGenTextures(1, &_texture);
	glBindTexture(GL_TEXTURE_2D, _texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// 设置采样方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // 变小时
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  // 变大时

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _pImage->getWidth(), _pImage->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, _pImage->getData());
}

void initShader(const char* _vertexPath, const char* _fragmentPath)
{
	_shader.initShader(_vertexPath, _fragmentPath);
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

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		_camera.move(CAMERA_MOVE::MOVE_FRONT);
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		_camera.move(CAMERA_MOVE::MOVE_BACK);
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		_camera.move(CAMERA_MOVE::MOVE_LEFT);
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		_camera.move(CAMERA_MOVE::MOVE_RIGHT);
	}
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	_camera.onMouseMove(xpos, ypos);
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

	glViewport(0, 0, _width, _height);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // 窗口大小被改变时就会被调用

	// 设置鼠标不可见
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback); //每次鼠标动时进行回调

	_camera.lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	_camera.setSpeed(0.005f);
	
	initModel();
	initTexture();
	
	initShader("vertexShader.glsl", "fragmentShader.glsl");

	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		// 绘图
		rend();

		glfwSwapBuffers(window); // 交换颜色缓冲区，防止屏幕碎裂
		glfwPollEvents(); // 处理用户交互事件
	}

	glfwTerminate();
	return 0;
}