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
	// 程序ID
	unsigned int ID;
	//构造方法
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	// 使用该渲染程序
	void use();
	//设置通用数据
	void setBool(const string &name, bool value) const;
	void setInt(const string &name, int value) const;
	void setFloat(const string &name, float value) const;
};
#endif // !_SHADER