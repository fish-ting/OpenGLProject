#include "Base.h"
#include "Shader.h"
#include "ffImage.h"
#include "Camera.h"


unsigned int VAO_cube = 0;
unsigned int VAO_sun = 0;  // 作为光源

glm::vec3 light_pos(1.0f);
glm::vec3 light_color(1.0f);

// 光照贴图
uint _textureBox = 0;
uint _textureSpec = 0;

ffImage* _pImage = NULL;

Shader _shader_cube;
Shader _shader_sun;
Shader _shader_dir;
Shader _shader_point;  // 点光源
Shader _shader_spot;   // 聚光灯
Shader _shader_scene;

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
	glm::vec3 cubePositions[] = {
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

	glm::vec3 pointLightPositions[] = {
		glm::vec3(0.7f,  0.2f,  2.0f),
		glm::vec3(2.3f, -3.3f, -4.0f),
		glm::vec3(-4.0f,  2.0f, -12.0f),
		glm::vec3(0.0f,  0.0f, -3.0f)
	};

	// 计算变换矩阵
	_camera.update();
	_projMatrix = glm::perspective(glm::radians(45.0f), (float)_width / (float)_height, 0.1f, 100.0f);

	glm::mat4 _modelMatrix(1.0f);
	_modelMatrix = glm::translate(_modelMatrix, glm::vec3(0.0f, 0.0f, -3.0f));

	glActiveTexture(GL_TEXTURE0); // 激活当前使用的texture0
	glBindTexture(GL_TEXTURE_2D, _textureBox);
	glActiveTexture(GL_TEXTURE1); // 激活当前使用的texture1
	glBindTexture(GL_TEXTURE_2D, _textureSpec);

	_shader_scene.start();

	_shader_scene.setMatrix("_viewMatrix", _camera.getMatrix());
	_shader_scene.setMatrix("_projMatrix", _projMatrix);
	_shader_scene.setVec3("view_pos", _camera.getPosition());

	// 传入物体材质属性
	_shader_scene.setInt("myMaterial.m_specular", 1);
	_shader_scene.setFloat("myMaterial.m_shiness", 32);

	// 传入光照属性
	// 平行光
	_shader_scene.setVec3("_dirLight.m_direction", glm::vec3(-0.2f, -1.0f, -0.3f));
	_shader_scene.setVec3("_dirLight.m_ambient", glm::vec3(0.05f, 0.05f, 0.05f));
	_shader_scene.setVec3("_dirLight.m_diffuse", glm::vec3(0.4f, 0.4f, 0.4f));
	_shader_scene.setVec3("_dirLight.m_specular", glm::vec3(0.5f, 0.5f, 0.5f));

	// 点光源 1
	_shader_scene.setVec3("_pointLight[0].m_pos", pointLightPositions[0]);
	_shader_scene.setVec3("_pointLight[0].m_ambient", glm::vec3(0.05f, 0.05f, 0.05f));
	_shader_scene.setVec3("_pointLight[0].m_diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
	_shader_scene.setVec3("_pointLight[0].m_specular", glm::vec3(1.0f, 1.0f, 1.0f));
	_shader_scene.setFloat("_pointLight[0].m_c", 1.0f);
	_shader_scene.setFloat("_pointLight[0].m_l", 0.09);
	_shader_scene.setFloat("_pointLight[0].m_q", 0.032);
	// 点光源 2
	_shader_scene.setVec3("_pointLight[1].m_pos", pointLightPositions[1]);
	_shader_scene.setVec3("_pointLight[1].m_ambient", glm::vec3(0.05f, 0.05f, 0.05f));
	_shader_scene.setVec3("_pointLight[1].m_diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
	_shader_scene.setVec3("_pointLight[1].m_specular", glm::vec3(1.0f, 1.0f, 1.0f));
	_shader_scene.setFloat("_pointLight[1].m_c", 1.0f);
	_shader_scene.setFloat("_pointLight[1].m_l", 0.09);
	_shader_scene.setFloat("_pointLight[1].m_q", 0.032);
	// 点光源 3
	_shader_scene.setVec3("_pointLight[2].m_pos", pointLightPositions[2]);
	_shader_scene.setVec3("_pointLight[2].m_ambient", glm::vec3(0.05f, 0.05f, 0.05f));
	_shader_scene.setVec3("_pointLight[2].m_diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
	_shader_scene.setVec3("_pointLight[2].m_specular", glm::vec3(1.0f, 1.0f, 1.0f));
	_shader_scene.setFloat("_pointLight[2].m_c", 1.0f);
	_shader_scene.setFloat("_pointLight[2].m_l", 0.09);
	_shader_scene.setFloat("_pointLight[2].m_q", 0.032);
	// 点光源 4
	_shader_scene.setVec3("_pointLight[3].m_pos", pointLightPositions[3]);
	_shader_scene.setVec3("_pointLight[3].m_ambient", glm::vec3(0.05f, 0.05f, 0.05f));
	_shader_scene.setVec3("_pointLight[3].m_diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
	_shader_scene.setVec3("_pointLight[3].m_specular", glm::vec3(1.0f, 1.0f, 1.0f));
	_shader_scene.setFloat("_pointLight[3].m_c", 1.0f);
	_shader_scene.setFloat("_pointLight[3].m_l", 0.09);
	_shader_scene.setFloat("_pointLight[3].m_q", 0.032);

	// 高光
	_shader_scene.setVec3("_spotLight.m_pos", _camera.getPosition());
	_shader_scene.setVec3("_spotLight.m_direction", _camera.getDirection());
	_shader_scene.setVec3("_spotLight.m_ambient", glm::vec3(0.0f, 0.0f, 0.0f));
	_shader_scene.setVec3("_spotLight.m_diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
	_shader_scene.setVec3("_spotLight.m_specular", glm::vec3(1.0f, 1.0f, 1.0f));
	_shader_scene.setFloat("_spotLight.m_c", 1.0f);
	_shader_scene.setFloat("_spotLight.m_l", 0.09);
	_shader_scene.setFloat("_spotLight.m_q", 0.032);
	_shader_scene.setFloat("_spotLight.m_cutOff", glm::cos(glm::radians(12.5f)));
	_shader_scene.setFloat("_spotLight.m_outCutOff", glm::cos(glm::radians(15.0f)));

	for (int i = 0; i < 10; i++)
	{
		_modelMatrix = glm::mat4(1.0f);
		_modelMatrix = glm::translate(_modelMatrix, cubePositions[i]);
		_modelMatrix = glm::rotate(_modelMatrix, glm::radians(i * 20.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		_shader_scene.setMatrix("_modelMatrix", _modelMatrix);
		
		glBindVertexArray(VAO_cube);
		glDrawArrays(GL_TRIANGLES, 0, 36); // 画36个点
	}

	_shader_scene.end();

	_shader_sun.start();
	_shader_sun.setMatrix("_modelMatrix", _modelMatrix);
	_shader_sun.setMatrix("_viewMatrix", _camera.getMatrix());
	_shader_sun.setMatrix("_projMatrix", _projMatrix);

	// 四个点光源
	for (int i = 0; i < 4; i++)
	{
		_modelMatrix = glm::mat4(1.0f);
		_modelMatrix = glm::translate(_modelMatrix, pointLightPositions[i]);
		_modelMatrix = glm::scale(_modelMatrix, glm::vec3(0.2f, 0.2f, 0.2f));
		_shader_sun.setMatrix("_modelMatrix", _modelMatrix);
		glBindVertexArray(VAO_sun);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	_shader_sun.end();

}

// 返回 VAO
uint createModel()
{
	uint _VAO = 0;
	uint _VBO = 0;

	// 坐标 - uv - 法线 , 12个三角形
	float vertices[] =
	{
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,           0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,           0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,           0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,           0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,           0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,           0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,           0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,           0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,           0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,           0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,           0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,           0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,           -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,           -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,           -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,           -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,           -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,           -1.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,           1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,           1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,           1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,           1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,           1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,           1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,           0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,           0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,           0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,           0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,           0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,           0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,           0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,           0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,           0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,           0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,           0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,           0.0f,  1.0f,  0.0f
	};

	//获取VAO，在关闭VAO前，期间所有的数据都会被纳入VAO的管理
	glGenVertexArrays(1, &_VAO);
	glBindVertexArray(_VAO);

	// 获取vbo的index，即到底要分配多少个vbo
	glGenBuffers(1, &_VBO);

	// 绑定vbo的index
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);

	// 给vbo分配显存空间，传输数据
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// 告诉shader数据解析方式
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(sizeof(float) * 3));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(sizeof(float) * 5));
	// 激活锚点
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	// 取消绑定
	glBindBuffer(GL_ARRAY_BUFFER, 0); // VBO 解绑
	glBindVertexArray(0); // VAO 解绑

	return _VAO;
}

uint createTexture(const char* _fileName)
{
	_pImage = ffImage::readFromFile(_fileName);
	uint _texture = 0;

	// 生成纹理对象并绑定
	glGenTextures(1, &_texture);
	glBindTexture(GL_TEXTURE_2D, _texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// 设置采样方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // 变小时
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  // 变大时

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _pImage->getWidth(), _pImage->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, _pImage->getData());
	return _texture;
}

void initShader()
{
	_shader_sun.initShader("vsunShader.glsl", "fsunShader.glsl");
	_shader_scene.initShader("sceneShaderv.glsl", "sceneShaderf.glsl");
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
	
	VAO_cube = createModel();
	VAO_sun = createModel();
	light_pos = glm::vec3(3.0f, 1.0f, -1.0f); // 设置光的位置
	light_color = glm::vec3(1.0f, 1.0f, 1.0f);

	_textureBox = createTexture("res/fish.jpg");
	_textureSpec = createTexture("res/specular.png");

	initShader();

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