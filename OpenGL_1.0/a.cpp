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
	// 初始化并配置glfw
	//---------------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// 配置窗口
	//---------------------------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		cout << "配置窗口出现错误!!!" << endl;
		return -1;
	}
	// 设置输出窗口
	//---------------------------------------
	glfwMakeContextCurrent(window);
	// 配置窗口渲染变化回调
	//---------------------------------------
	glfwSetFramebufferSizeCallback(window, fragmentbufferSizeCallback);
	//配置GLAD
	//---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "加载GLAD出现错误!!!" << endl;
		return -1;
	}
	//// 创建渲染器 
	////---------------------------------------
	//// 顶点渲染器
	//int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//glCompileShader(vertexShader);
	//// 获取顶点渲染器编译错误原因
	//int success;
	//char info[512];
	//glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	//if (!success)
	//{
	//	glGetShaderInfoLog(vertexShader, 512, NULL, info);
	//	cout << "编译顶点渲染器出现错误 --- " << info << endl;
	//	return -1;
	//}
	//// 编译片段渲染器
	//int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	//glCompileShader(fragmentShader);
	////获取片段渲染器编译错误原因
	//glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	//if (!success)
	//{
	//	glGetShaderInfoLog(fragmentShader, 512, NULL, info);
	//	cout << "编译片段渲染器出现错误 --- " << info << endl;
	//	return -1;
	//}
	//// 配置渲染程序
	//int shaderProgram = glCreateProgram();
	//// 配置顶点渲染器
	//glAttachShader(shaderProgram, vertexShader);
	//// 配置片段渲染器
	//glAttachShader(shaderProgram, fragmentShader);
	//// 连接渲染程序
	//glLinkProgram(shaderProgram);
	////获取渲染程序连接错误原因
	//glGetShaderiv(shaderProgram, GL_LINK_STATUS, &success);
	//if (!success)
	//{
	//	glGetProgramInfoLog(shaderProgram, 512, NULL, info);
	//	cout << "连接渲染器程序出错 --- " << info << endl;
	//}
	//// 释放渲染器
	//glDeleteShader(vertexShader);
	//glDeleteShader(fragmentShader);
	
	// 渲染程序对象
	Shader shaderProgram("./shader.vs", "./shader.fs");

	//创建纹理
	unsigned int texture1;
	glGenTextures(1, &texture1);
	// 启用纹理0
	glActiveTexture(GL_TEXTURE0);
	//绑定纹理
	glBindTexture(GL_TEXTURE_2D, texture1);
	//配置纹理取样方式
	// 在x轴复制模式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	// 在y轴为复制
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// 缩小时为线性采样
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	// 放大时为线性采样
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// 加载纹理图
	int width, height, nrChannels;
	unsigned char *data = stbi_load("./container.jpg", &width, &height, &nrChannels, 0);
	if (data) 
	{
		//纹理加载纹理数据
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		// 释放读取的纹理数据
		cout << "纹理图颜色通道数 ---- " << nrChannels << endl;
	}
	else 
	{
		cout << "读取纹理数据出现错误 " << endl;
	}
	stbi_image_free(data);

	//创建纹理2
	unsigned int texture2;
	glGenTextures(1, &texture2);
	// 启用纹理1
	glActiveTexture(GL_TEXTURE1);
	//绑定纹理
	glBindTexture(GL_TEXTURE_2D, texture2);
	//配置纹理取样方式
	// 在x轴复制模式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	// 在y轴为复制
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	// 缩小时为线性采样
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	// 放大时为线性采样
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// 加载纹理图2 --- 可以作为材质
	stbi_set_flip_vertically_on_load(true);
	data = stbi_load("./awesomeface.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else 
	{
		cout << "加载纹理2出现错误" << endl;
	}
	stbi_image_free(data);

	// 渲染图形
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
		// 顶点位置			// 颜色				// 纹理坐标
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
	// 创建并绑定顶点数组对象
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//创建并绑定顶点缓冲对象
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesWithTexture), verticesWithTexture, GL_STATIC_DRAW);

	// 创建元素缓冲对象
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//设置步进
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	// 在数据中设置颜色
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	// 启用顶点缓冲对象
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	// 绘制
	//--------------------------------------------------
	while (!glfwWindowShouldClose(window))
	{
		processInputEvent(window);
		glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// 启用纹理0
		glActiveTexture(GL_TEXTURE0);
		// 绑定纹理
		glBindTexture(GL_TEXTURE_2D, texture1);
		// 启用纹理1
		glActiveTexture(GL_TEXTURE1);
		// 绑定纹理
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

	// 再次清楚所有数据
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	//清除资源
	//-------------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

// 渲染缓存变化回调
void fragmentbufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

// 按键事件统一处理
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