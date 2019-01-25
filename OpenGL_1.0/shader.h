#ifndef _SHADER
#define _SHADER
#include "Include/glad/glad.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class Shader
{
public:
	// ����ID
	unsigned int ID;
	//���췽��
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	// ʹ�ø���Ⱦ����
	void use();
	//����ͨ������
	void setBool(const string &name, bool value) const;
	void setInt(const string &name, int value) const;
	void setFloat(const string &name, float value) const;
};
#endif // !_SHADER