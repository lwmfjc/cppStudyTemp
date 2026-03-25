//编译器第一次遇到这个文件，正常读取内容。
//编译器会记下这个文件的物理路径。
//当后续代码再次尝试 #include 这个路径的文件时，编译器直接跳过，不再读取。
#pragma once

#include <GL/glew.h> 

//_debugbreak() 是msvc特有的
//__FILE__和__LINE__ 是所有编译器都支持的
//#x：字符串化操作符。它会将你传入的代码直接转成字符串
//__FILE__ 和 __LINE__：编译器内置宏，自动获取当前代码所在的文件名和行号
#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x,__FILE__,__LINE__));

void GLClearError();

bool GLLogCall(const char* function,
	const char* file, int line);