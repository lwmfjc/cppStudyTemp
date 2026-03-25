#include "Render.h"
#include <iostream>

void GLClearError()
{
	//直到不是GL_NO_ERROR，就退出while循环
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function,
	const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error](" << error << "): "
			<< function << " " << file << ":" << line << std::endl;
		return false;
	}

	return true;
}