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
	// 创建渲染器 
	//---------------------------------------
	// 顶点渲染器
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	// 获取顶点渲染器编译错误原因
	int success;
	char info[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) 
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, info);
		cout << "编译顶点渲染器出现错误 --- " << info << endl;
		return -1;
	}
	// 编译片段渲染器
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	//获取片段渲染器编译错误原因
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, info);
		cout << "编译片段渲染器出现错误 --- " << info << endl;
		return -1;
	}
	// 配置渲染程序
	int shaderProgram = glCreateProgram();
	// 配置顶点渲染器
	glAttachShader(shaderProgram, vertexShader);
	// 配置片段渲染器
	glAttachShader(shaderProgram, fragmentShader);
	// 连接渲染程序
	glLinkProgram(shaderProgram);
	//获取渲染程序连接错误原因
	glGetShaderiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, info);
		cout << "连接渲染器程序出错 --- " << info << endl;
	}
	// 释放渲染器
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	
	// 渲染图形
	//---------------------------------------
	const float vertices[] =
	{
		0.0f, 0.5f, 0.0f,
		0.5, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f
	};
	// 创建并绑定顶点数组对象
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//创建并绑定顶点缓冲对象
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//设置步进
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
	// 启用顶点缓冲对象
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// 绘制
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
}