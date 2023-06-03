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
	// ��ɫ�����������
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// ������ȼ��
	glEnable(GL_DEPTH_TEST);

	// ����׼��
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

	// ����任����
	//_viewMatrix = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0, 1, 0));
	_camera.update();
	_projMatrix = glm::perspective(glm::radians(45.0f), (float)_width / (float)_height, 0.1f, 100.0f);


	//glBindTexture(GL_TEXTURE_2D, _texture);

	// �����������

	for (int i = 0; i < 10; i++) {
		glm::mat4 _modelMatrix(1.0f);
		_modelMatrix = glm::translate(_modelMatrix, modelVecs[i]);
		_modelMatrix = glm::rotate(_modelMatrix, glm::radians((float)glfwGetTime() * (i + 1) * 10), glm::vec3(0.0f, 1.0f, 0.0f));

		_shader.start();
		_shader.setMatrix("_modelMatrix", _modelMatrix);
		_shader.setMatrix("_viewMatrix", _camera.getMatrix());
		_shader.setMatrix("_projMatrix", _projMatrix);

		glBindVertexArray(VAO);

		glDrawArrays(GL_TRIANGLES, 0, 36); // ��36����
		_shader.end();
	}
}

// ����shader���ݽ�����ʽ
// ����ê��

void initModel()
{
	// ���� - uv , 12��������
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

	//��ȡVAO���ڹر�VAOǰ���ڼ����е����ݶ��ᱻ����VAO�Ĺ���
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// ��ȡvbo��index��������Ҫ������ٸ�vbo
	glGenBuffers(1, &VBO);

	// ��vbo��index
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// ��vbo�����Դ�ռ䣬��������
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// ����shader���ݽ�����ʽ
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(sizeof(float) * 3));

	// ����ê��
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	// ȡ����
	glBindBuffer(GL_ARRAY_BUFFER, 0); // VBO ���
	glBindVertexArray(0); // VAO ���
}

void initTexture()
{
	_pImage = ffImage::readFromFile("res/fish.jpg");

	// ����������󲢰�
	glGenTextures(1, &_texture);
	glBindTexture(GL_TEXTURE_2D, _texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// ���ò�����ʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // ��Сʱ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  // ���ʱ

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
	// ������⵱ǰ�����Ƿ񱻰��� ESC ��ť
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

int main()
{
	// ��ʼ�����ڿ�
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}
	// 4.3 �汾
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
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // ���ڴ�С���ı�ʱ�ͻᱻ����

	_camera.lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	_camera.setSpeed(0.005f);
	
	initModel();
	initTexture();
	
	initShader("vertexShader.glsl", "fragmentShader.glsl");

	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		// ��ͼ
		rend();

		glfwSwapBuffers(window); // ������ɫ����������ֹ��Ļ����
		glfwPollEvents(); // �����û������¼�
	}

	glfwTerminate();
	return 0;
}