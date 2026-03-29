#pragma once
#include <vector>
#include <GL/glew.h>
#include "Renderer.h"

struct VertexBufferElement
{
	unsigned int type;
	int count;
	unsigned char normalized;

	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT: return 4;
		case GL_UNSIGNED_INT: return 4;
		case GL_UNSIGNED_BYTE: return 1;

		}
		ASSERT(false);
		return 0;
	}
};

class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> m_Elements;
	unsigned int m_Stride;//步长
public :
	VertexBufferLayout()
		:m_Stride(0) {}

	//解释一下，第n个push的就是第n组属性的布局
	template<typename T>
	void Push(int cout)
	{
		static_assert(false);
	}

	//位置 ($x, y, z$)
	template<>
	void Push<float>(int count)
	{
		m_Elements.push_back({ GL_FLOAT,count,GL_FALSE });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
	}

	//ID、索引
	template<>
	void Push<unsigned int >(int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_INT,count,GL_FALSE });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
	}

	//颜色 (R, G, B, A)
	//如果你设置 GL_TRUE (归一化)：OpenGL 会自动帮你做除法。比如你传 255，Shader 拿到的是 $255 / 255 = 1.0$；你传 128，Shader 拿到的是 $0.5$
	template<>
	void Push<unsigned char>(int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_BYTE,count,GL_TRUE });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
	}

	inline const std::vector<VertexBufferElement> GetElements() const { return m_Elements; }
	inline unsigned int GetStrde() const { return m_Stride; }
};
