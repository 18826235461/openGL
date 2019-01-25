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
	// �������־λ�Կ����������쳣
	vShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
	fShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
	try
	{
		// ���ļ���
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		stringstream vShaderStream, fShaderStream;
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		//�ر��ļ���
		vShaderFile.close();
		fShaderFile.close();
		//����ת��Ϊ�ַ���
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (exception &)
	{
		cout << "���ļ�����" << endl;
	};
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();
	// ������Ⱦ��
	unsigned int vertex, fragment;
	int success;
	char infoLog[512];
	// ���붥����Ⱦ��
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		cout << "���붥����Ⱦ������ --- " << infoLog << endl;
	}
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		cout << "����Ƭ����Ⱦ������ --- " << infoLog << endl;
	}

	// ������Ⱦ����
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ID, GL_LINK_STATUS, NULL, infoLog);
		cout << "������Ⱦ������� --- " << infoLog << endl;
	}

	// ɾ���������Ⱦ��
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
