#include "Include/glad/glad.h"
#include "Include/glfw3.h"
#include <iostream>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

using namespace std;

void fragmentbufferSizeCallback(GLFWwindow* window, int width, int height);
void processInputEvent(GLFWwindow* window);

const char* vertexShaderSource = "#version 330 core\n"
"layout(location = 0) in vec3 aPos;\n "
"void main(){\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main(){\n"
"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";

int main()
{
	// ��ʼ��������glfw
	//---------------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// ���ô���
	//---------------------------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		cout << "���ô��ڳ��ִ���!!!" << endl;
		return -1;
	}
	// �����������
	//---------------------------------------
	glfwMakeContextCurrent(window);
	// ���ô�����Ⱦ�仯�ص�
	//---------------------------------------
	glfwSetFramebufferSizeCallback(window, fragmentbufferSizeCallback);
	//����GLAD
	//---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
	{
		cout << "����GLAD���ִ���!!!" << endl;
		return -1;
	}
	// ������Ⱦ�� 
	//---------------------------------------
	// ������Ⱦ��
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	// ��ȡ������Ⱦ���������ԭ��
	int success;
	char info[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) 
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, info);
		cout << "���붥����Ⱦ�����ִ��� --- " << info << endl;
		return -1;
	}
	// ����Ƭ����Ⱦ��
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	//��ȡƬ����Ⱦ���������ԭ��
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, info);
		cout << "����Ƭ����Ⱦ�����ִ��� --- " << info << endl;
		return -1;
	}
	// ������Ⱦ����
	int shaderProgram = glCreateProgram();
	// ���ö�����Ⱦ��
	glAttachShader(shaderProgram, vertexShader);
	// ����Ƭ����Ⱦ��
	glAttachShader(shaderProgram, fragmentShader);
	// ������Ⱦ����
	glLinkProgram(shaderProgram);
	//��ȡ��Ⱦ�������Ӵ���ԭ��
	glGetShaderiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, info);
		cout << "������Ⱦ��������� --- " << info << endl;
	}
	// �ͷ���Ⱦ��
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	
	// ��Ⱦͼ��
	//---------------------------------------
	const float vertices[] =
	{
		0.0f, 0.5f, 0.0f,
		0.5, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f
	};
	// �������󶨶����������
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//�������󶨶��㻺�����
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//���ò���
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
	// ���ö��㻺�����
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// ����
	//--------------------------------------------------
	while (!glfwWindowShouldClose(window)) 
	{
		processInputEvent(window);
		glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// �ٴ������������
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	//�����Դ
	//-------------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

// ��Ⱦ����仯�ص�
void fragmentbufferSizeCallback(GLFWwindow* window, int width, int height) 
{
	glViewport(0, 0, width, height);
}

// �����¼�ͳһ����
void processInputEvent(GLFWwindow* window) 
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) 
	{
		glfwSetWindowShouldClose(window, true);
	}
}