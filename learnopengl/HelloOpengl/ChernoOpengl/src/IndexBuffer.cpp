#include "IndexBuffer.h"
#include "Render.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
	:m_Count(count)
{  
	ASSERT(sizeof(unsigned int) == sizeof(GLuint));
	// 生成一个缓冲区 ID
	GLCall(glGenBuffers(1, &m_RendererID));
	// 绑定该 ID 到元素数组缓冲区 (Element Array Buffer)插槽，
	//也称索引缓冲区对象
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
	// 将顶点数据从 CPU 内存拷贝到 GPU 显存，设为静态读取模式
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int),
		data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_RendererID));
}

void IndexBuffer::Bind() const
{
	// 绑定该 ID 到元素数组缓冲区插槽
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}

void IndexBuffer::Unbind() const
{
	// 绑定该 ID 到元素数组缓冲区插槽
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
