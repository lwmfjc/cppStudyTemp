#include "Renderer.h"
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

void Renderer::Clear() const
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{

	//绘图前重新绑定
	shader.Bind();

	//必须先绑定program，因为vao不负责着色器程序的切换
	va.Bind();

	//这个可以不用，已经在va中录制了
	//ib.Bind();

	GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));

	//绘制后经常不需要再解绑，因为这会消耗性能，而且
	//我们经常会在下一帧继续使用它们并覆盖 
}
