#include "Base.h"
#include "Shader.h"
#include "ffImage.h"
#include "Camera.h"


unsigned int VAO_cube = 0;
unsigned int VAO_sun = 0;  // ��Ϊ��Դ

glm::vec3 light_pos(1.0f);
glm::vec3 light_color(1.0f);

// ������ͼ
uint _textureBox = 0;
uint _textureSpec = 0;

ffImage* _pImage = NULL;

Shader _shader_cube;
Shader _shader_sun;
Shader _shader_dir;
Shader _shader_point;  // ���Դ
Shader _shader_spot;   // �۹��
Shader _shader_scene;
Shader _shader_color;

glm::mat4 _viewMatrix(1.0f);
glm::mat4 _projMatrix(1.0f);

int _width = 820;
int _height = 820;

Camera _camera;

void rend()
{
	// ������ȼ��
	glEnable(GL_DEPTH_TEST);
	// ����ģ����
	glEnable(GL_STENCIL_TEST);
	// ����д��
	glStencilMask(0xFF);

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	// ��ɫ����ȡ�ģ������
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	// ����׼��
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

	// ����任����
	_camera.update();
	_projMatrix = glm::perspective(glm::radians(45.0f), (float)_width / (float)_height, 0.1f, 100.0f);
	glm::mat4 _modelMatrix(1.0f);
	_modelMatrix = glm::translate(_modelMatrix, glm::vec3(0.0f, 0.0f, -3.0f));

	// ��������
	glActiveTexture(GL_TEXTURE0); // ���ǰʹ�õ�texture0
	glBindTexture(GL_TEXTURE_2D, _textureBox);
	glActiveTexture(GL_TEXTURE1); // ���ǰʹ�õ�texture1
	glBindTexture(GL_TEXTURE_2D, _textureSpec);

	_shader_scene.start();

	_shader_scene.setMatrix("_viewMatrix", _camera.getMatrix());
	_shader_scene.setMatrix("_projMatrix", _projMatrix);
	_shader_scene.setVec3("view_pos", _camera.getPosition());

	// ���������������
	_shader_scene.setInt("myMaterial.m_specular", 1);
	_shader_scene.setFloat("myMaterial.m_shiness", 32);

	// �����������
	// ƽ�й�
	_shader_scene.setVec3("_dirLight.m_direction", glm::vec3(-0.2f, -1.0f, -0.3f));
	_shader_scene.setVec3("_dirLight.m_ambient", glm::vec3(0.05f, 0.05f, 0.05f));
	_shader_scene.setVec3("_dirLight.m_diffuse", glm::vec3(0.4f, 0.4f, 0.4f));
	_shader_scene.setVec3("_dirLight.m_specular", glm::vec3(0.5f, 0.5f, 0.5f));

	// ���Դ 1
	_shader_scene.setVec3("_pointLight[0].m_pos", pointLightPositions[0]);
	_shader_scene.setVec3("_pointLight[0].m_ambient", glm::vec3(0.05f, 0.05f, 0.05f));
	_shader_scene.setVec3("_pointLight[0].m_diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
	_shader_scene.setVec3("_pointLight[0].m_specular", glm::vec3(1.0f, 1.0f, 1.0f));
	_shader_scene.setFloat("_pointLight[0].m_c", 1.0f);
	_shader_scene.setFloat("_pointLight[0].m_l", 0.09);
	_shader_scene.setFloat("_pointLight[0].m_q", 0.032);
	// ���Դ 2
	_shader_scene.setVec3("_pointLight[1].m_pos", pointLightPositions[1]);
	_shader_scene.setVec3("_pointLight[1].m_ambient", glm::vec3(0.05f, 0.05f, 0.05f));
	_shader_scene.setVec3("_pointLight[1].m_diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
	_shader_scene.setVec3("_pointLight[1].m_specular", glm::vec3(1.0f, 1.0f, 1.0f));
	_shader_scene.setFloat("_pointLight[1].m_c", 1.0f);
	_shader_scene.setFloat("_pointLight[1].m_l", 0.09);
	_shader_scene.setFloat("_pointLight[1].m_q", 0.032);
	// ���Դ 3
	_shader_scene.setVec3("_pointLight[2].m_pos", pointLightPositions[2]);
	_shader_scene.setVec3("_pointLight[2].m_ambient", glm::vec3(0.05f, 0.05f, 0.05f));
	_shader_scene.setVec3("_pointLight[2].m_diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
	_shader_scene.setVec3("_pointLight[2].m_specular", glm::vec3(1.0f, 1.0f, 1.0f));
	_shader_scene.setFloat("_pointLight[2].m_c", 1.0f);
	_shader_scene.setFloat("_pointLight[2].m_l", 0.09);
	_shader_scene.setFloat("_pointLight[2].m_q", 0.032);
	// ���Դ 4
	_shader_scene.setVec3("_pointLight[3].m_pos", pointLightPositions[3]);
	_shader_scene.setVec3("_pointLight[3].m_ambient", glm::vec3(0.05f, 0.05f, 0.05f));
	_shader_scene.setVec3("_pointLight[3].m_diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
	_shader_scene.setVec3("_pointLight[3].m_specular", glm::vec3(1.0f, 1.0f, 1.0f));
	_shader_scene.setFloat("_pointLight[3].m_c", 1.0f);
	_shader_scene.setFloat("_pointLight[3].m_l", 0.09);
	_shader_scene.setFloat("_pointLight[3].m_q", 0.032);

	// �߹�
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

	glStencilFunc(GL_ALWAYS, 1, 0xFF);  // ��Զͨ��
	glStencilMask(0xFF); // ����д��

	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	glStencilFunc(GL_ALWAYS, 1, 0xFF);  // ��Զͨ��
	glStencilMask(0xFF); // ����д��
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	for (int i = 0; i < 10; i++)
	{
		_modelMatrix = glm::mat4(1.0f);
		_modelMatrix = glm::translate(_modelMatrix, cubePositions[i]);
		_modelMatrix = glm::rotate(_modelMatrix, glm::radians(i * 20.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		_shader_scene.setMatrix("_modelMatrix", _modelMatrix);
		
		glBindVertexArray(VAO_cube);
		glDrawArrays(GL_TRIANGLES, 0, 36); // ��36����
	}

	_shader_scene.end();

	// ���Ƹ߹��Ե
	glStencilFunc(GL_NOTEQUAL, 1, 0xFF);  // ������1��ͨ��
	glStencilMask(0x00); // ������д��

	_shader_color.start();
	_shader_color.setMatrix("_viewMatrix", _camera.getMatrix());
	_shader_color.setMatrix("_projMatrix", _projMatrix);

	for (int i = 0; i < 10; i++)
	{
		_modelMatrix = glm::mat4(1.0f);
		_modelMatrix = glm::translate(_modelMatrix, cubePositions[i]);
		_modelMatrix = glm::rotate(_modelMatrix, glm::radians(i * 20.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		_modelMatrix = glm::scale(_modelMatrix, glm::vec3(1.05f, 1.05f, 1.05f));
		
		_shader_color.setMatrix("_modelMatrix", _modelMatrix);

		glBindVertexArray(VAO_cube);
		glDrawArrays(GL_TRIANGLES, 0, 36); // ��36����
	}

	_shader_color.end();


	glStencilFunc(GL_ALWAYS, 1, 0xFF);  // ͨ��
	_shader_sun.start();
	_shader_sun.setMatrix("_modelMatrix", _modelMatrix);
	_shader_sun.setMatrix("_viewMatrix", _camera.getMatrix());
	_shader_sun.setMatrix("_projMatrix", _projMatrix);

	// �ĸ����Դ
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

// ���� VAO
uint createModel()
{
	uint _VAO = 0;
	uint _VBO = 0;

	// ���� - uv - ���� , 12��������
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

	//��ȡVAO���ڹر�VAOǰ���ڼ����е����ݶ��ᱻ����VAO�Ĺ���
	glGenVertexArrays(1, &_VAO);
	glBindVertexArray(_VAO);

	// ��ȡvbo��index��������Ҫ������ٸ�vbo
	glGenBuffers(1, &_VBO);

	// ��vbo��index
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);

	// ��vbo�����Դ�ռ䣬��������
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// ����shader���ݽ�����ʽ
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(sizeof(float) * 3));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(sizeof(float) * 5));
	// ����ê��
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	// ȡ����
	glBindBuffer(GL_ARRAY_BUFFER, 0); // VBO ���
	glBindVertexArray(0); // VAO ���

	return _VAO;
}

uint createTexture(const char* _fileName)
{
	_pImage = ffImage::readFromFile(_fileName);
	uint _texture = 0;

	// ����������󲢰�
	glGenTextures(1, &_texture);
	glBindTexture(GL_TEXTURE_2D, _texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// ���ò�����ʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // ��Сʱ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  // ���ʱ

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _pImage->getWidth(), _pImage->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, _pImage->getData());
	return _texture;
}

void initShader()
{
	_shader_sun.initShader("vsunShader.glsl", "fsunShader.glsl");
	_shader_scene.initShader("sceneShaderv.glsl", "sceneShaderf.glsl");
	_shader_color.initShader("colorShaderv.glsl", "colorShaderf.glsl");
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

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	_camera.onMouseMove(xpos, ypos);
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

	// ������겻�ɼ�
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback); //ÿ����궯ʱ���лص�

	_camera.lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	_camera.setSpeed(0.005f);
	
	VAO_cube = createModel();
	VAO_sun = createModel();
	light_pos = glm::vec3(3.0f, 1.0f, -1.0f); // ���ù��λ��
	light_color = glm::vec3(1.0f, 1.0f, 1.0f);

	_textureBox = createTexture("res/fish.jpg");
	_textureSpec = createTexture("res/specular.png");

	initShader();

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