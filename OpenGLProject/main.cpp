#include "Base.h"
#include "Shader.h"

unsigned int VAO = 0;
unsigned int VBO = 0;

Shader _shader;

void rend()
{
	_shader.start();

	glBindVertexArray(VAO);

	glDrawArrays(GL_TRIANGLES, 0, 3);
	
	_shader.end();
}

// 告诉shader数据解析方式
// 激活锚点

void initModel()
{
	float vertices[] =
	{
		-0.5f, -0.5, 0.0f,  1.0f, 0.0f, 0.0f, 
		0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
		0.0f, 0.5f, 0.0f,   0.0f, 0.0f, 1.0f
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(sizeof(float) * 3));
	
	// 激活锚点
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	// 取消绑定
	glBindBuffer(GL_ARRAY_BUFFER, 0); // VBO 解绑
	glBindVertexArray(0); // VAO 解绑
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