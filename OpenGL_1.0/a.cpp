#include "Include/glad/glad.h"
#include "Include/glfw3.h"
#include <iostream>
#include <cmath>
#include "shader.h"
#include "stb_image.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

using namespace std;

void fragmentbufferSizeCallback(GLFWwindow* window, int width, int height);
void processInputEvent(GLFWwindow* window);

const char* vertexShaderSource = "#version 330 core\n"
"layout(location = 0) in vec3 aPos;\n "
"layout(location = 1) in vec3 aColor;\n"
"out vec3 ourColor;"
"void main(){\n"
"	gl_Position = vec4(aPos, 1.0);\n"
"	ourColor = aColor;"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"in vec3 ourColor;\n"
"out vec4 FragColor;\n"
"void main(){\n"
"	FragColor = vec4(ourColor, 1.0f);\n"
"}\0";

float mixValue = 0.2f;

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
	//// ������Ⱦ�� 
	////---------------------------------------
	//// ������Ⱦ��
	//int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//glCompileShader(vertexShader);
	//// ��ȡ������Ⱦ���������ԭ��
	//int success;
	//char info[512];
	//glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	//if (!success)
	//{
	//	glGetShaderInfoLog(vertexShader, 512, NULL, info);
	//	cout << "���붥����Ⱦ�����ִ��� --- " << info << endl;
	//	return -1;
	//}
	//// ����Ƭ����Ⱦ��
	//int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	//glCompileShader(fragmentShader);
	////��ȡƬ����Ⱦ���������ԭ��
	//glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	//if (!success)
	//{
	//	glGetShaderInfoLog(fragmentShader, 512, NULL, info);
	//	cout << "����Ƭ����Ⱦ�����ִ��� --- " << info << endl;
	//	return -1;
	//}
	//// ������Ⱦ����
	//int shaderProgram = glCreateProgram();
	//// ���ö�����Ⱦ��
	//glAttachShader(shaderProgram, vertexShader);
	//// ����Ƭ����Ⱦ��
	//glAttachShader(shaderProgram, fragmentShader);
	//// ������Ⱦ����
	//glLinkProgram(shaderProgram);
	////��ȡ��Ⱦ�������Ӵ���ԭ��
	//glGetShaderiv(shaderProgram, GL_LINK_STATUS, &success);
	//if (!success)
	//{
	//	glGetProgramInfoLog(shaderProgram, 512, NULL, info);
	//	cout << "������Ⱦ��������� --- " << info << endl;
	//}
	//// �ͷ���Ⱦ��
	//glDeleteShader(vertexShader);
	//glDeleteShader(fragmentShader);
	
	// ��Ⱦ�������
	Shader shaderProgram("./shader.vs", "./shader.fs");

	//��������
	unsigned int texture1;
	glGenTextures(1, &texture1);
	// ��������0
	glActiveTexture(GL_TEXTURE0);
	//������
	glBindTexture(GL_TEXTURE_2D, texture1);
	//��������ȡ����ʽ
	// ��x�Ḵ��ģʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	// ��y��Ϊ����
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// ��СʱΪ���Բ���
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	// �Ŵ�ʱΪ���Բ���
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// ��������ͼ
	int width, height, nrChannels;
	unsigned char *data = stbi_load("./container.jpg", &width, &height, &nrChannels, 0);
	if (data) 
	{
		//���������������
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		// �ͷŶ�ȡ����������
		cout << "����ͼ��ɫͨ���� ---- " << nrChannels << endl;
	}
	else 
	{
		cout << "��ȡ�������ݳ��ִ��� " << endl;
	}
	stbi_image_free(data);

	//��������2
	unsigned int texture2;
	glGenTextures(1, &texture2);
	// ��������1
	glActiveTexture(GL_TEXTURE1);
	//������
	glBindTexture(GL_TEXTURE_2D, texture2);
	//��������ȡ����ʽ
	// ��x�Ḵ��ģʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	// ��y��Ϊ����
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	// ��СʱΪ���Բ���
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	// �Ŵ�ʱΪ���Բ���
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// ��������ͼ2 --- ������Ϊ����
	stbi_set_flip_vertically_on_load(true);
	data = stbi_load("./awesomeface.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else 
	{
		cout << "��������2���ִ���" << endl;
	}
	stbi_image_free(data);

	// ��Ⱦͼ��
	//---------------------------------------
	const float vertices[] =
	{
		0.0f, 0.5f, 0.0f,
		0.5, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f
	};

	const float vertices2[] =
	{
		-0.5,0.5f, 0.0f,
		0.5f,0.5f,0.0f,
		0.5,-0.5f,0.0f,
		-0.5f,-0.5f,0.0f
	};

	const float vertices3[] =
	{
		0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f
	};

	const float verticesWithTexture[] = 
	{
		// ����λ��			// ��ɫ				// ��������
		0.5f, 0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	1.0f, 1.0f,   // top right
		0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	1.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f, 1.0f,	0.0f, 0.0f,   // bottom left
		-0.5f, 0.5f, 0.0f,		1.0f, 1.0f, 0.0f,		0.0f, 1.0f    // top left 
	};

	const unsigned int indices[] =
	{
		0,1,3,
		1,2,3
	};
	// �������󶨶����������
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//�������󶨶��㻺�����
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesWithTexture), verticesWithTexture, GL_STATIC_DRAW);

	// ����Ԫ�ػ������
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//���ò���
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	// ��������������ɫ
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	// ���ö��㻺�����
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	// ����
	//--------------------------------------------------
	while (!glfwWindowShouldClose(window))
	{
		processInputEvent(window);
		glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// ��������0
		glActiveTexture(GL_TEXTURE0);
		// ������
		glBindTexture(GL_TEXTURE_2D, texture1);
		// ��������1
		glActiveTexture(GL_TEXTURE1);
		// ������
		glBindTexture(GL_TEXTURE_2D, texture2);
		//glUseProgram(shaderProgram);
		shaderProgram.use();
		shaderProgram.setInt("texture1", 0);
		shaderProgram.setInt("texture2", 1);
		shaderProgram.setFloat("mixValue", mixValue);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) 
	{
		mixValue += 0.01f;
		if (mixValue > 1.0f) 
		{
			mixValue = 1.0f;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) 
	{
		mixValue -= 0.01f;
		if (mixValue < 0.0f)
		{
			mixValue = 0.0f;
		}
	}
}