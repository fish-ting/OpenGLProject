#include "Base.h"
#include "Shader.h"

unsigned int VAO = 0;
unsigned int VBO = 0;

Shader _shader;

void rend()
{
	_shader.start();

	glBindVertexArray(VAO);

	//glDrawArrays(GL_TRIANGLES, 0, 3);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // ��������

	_shader.end();
}

// ����shader���ݽ�����ʽ
// ����ê��

void initModel()
{
	float vertices[] =
	{
		0.5f,  0.5,  0.0f,  1.0f, 0.0f, 0.0f, 
		0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,
		-0.5f, 0.5f, 0.0f,    0.0f, 1.0f, 0.0f
	};

	// ��������
	unsigned int indices[] = 
	{
		0, 1, 3,
		1, 2, 3
	};

	//��ȡVAO���ڹر�VAOǰ���ڼ����е����ݶ��ᱻ����VAO�Ĺ���
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// ����EBO
	unsigned int EBO = 0;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	// ��ȡvbo��index��������Ҫ������ٸ�vbo
	glGenBuffers(1, &VBO);

	// ��vbo��index
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// ��vbo�����Դ�ռ䣬��������
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// ����shader���ݽ�����ʽ
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(sizeof(float) * 3));
	
	// ����ê��
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	// ȡ����
	glBindBuffer(GL_ARRAY_BUFFER, 0); // VBO ���
	glBindVertexArray(0); // VAO ���
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

	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // ���ڴ�С���ı�ʱ�ͻᱻ����

	initModel();
	initShader("vertexShader.glsl", "fragmentShader.glsl");

	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// ��ͼ
		rend();

		glfwSwapBuffers(window); // ������ɫ����������ֹ��Ļ����
		glfwPollEvents(); // �����û������¼�
	}

	glfwTerminate();
	return 0;
}