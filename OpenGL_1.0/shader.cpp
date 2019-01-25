//#include "Include/glad/glad.h"
//#include "Include/glfw3.h"
#include "shader.h"
#include <iostream>
#include <fstream>

Shader::Shader(const GLchar * vertexPath, const GLchar * fragmentPath){
	string vertexCode;
	string fragmentCode;
	ifstream vShaderFile;
	ifstream fShaderFile;
	// 清除流标志位以可以正常抛异常
	vShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
	fShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
	try
	{
		// 打开文件流
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		stringstream vShaderStream, fShaderStream;
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		//关闭文件流
		vShaderFile.close();
		fShaderFile.close();
		//将流转换为字符串
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (exception &)
	{
		cout << "打开文件错误" << endl;
	};
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();
	// 编译渲染器
	unsigned int vertex, fragment;
	int success;
	char infoLog[512];
	// 编译顶点渲染器
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		cout << "编译顶点渲染器出错 --- " << infoLog << endl;
	}
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		cout << "编译片段渲染器出错 --- " << infoLog << endl;
	}

	// 配置渲染程序
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ID, GL_LINK_STATUS, NULL, infoLog);
		cout << "配置渲染程序出错 --- " << infoLog << endl;
	}

	// 删除编译的渲染器
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::use()
{
	glUseProgram(ID);
}

void Shader::setBool(const string &name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const string &name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const string &name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
