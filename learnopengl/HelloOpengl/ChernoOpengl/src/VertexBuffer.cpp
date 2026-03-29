#include "VertexBuffer.h"
#include "Renderer.h"


VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{ 
	// 生成一个缓冲区 ID
	GLCall(glGenBuffers(1, &m_RendererID));
	// 绑定该 ID 到顶点缓冲区插槽
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
	// 将顶点数据从 CPU 内存拷贝到 GPU 显存，设为静态读取模式
	GLCall(glBufferData(GL_ARRAY_BUFFER, size,
		data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_RendererID));
}

void VertexBuffer::Bind() const
{
	// 绑定该 ID 到顶点缓冲区插槽
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void VertexBuffer::Unbind() const
{
	// 绑定该 ID 到顶点缓冲区插槽
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
