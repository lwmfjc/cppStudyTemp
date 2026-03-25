#pragma once

//专门处理顶点缓冲区的生成、绑定、解绑及内存释放
class VertexBuffer
{
private:
	//一个相关的渲染器id
	unsigned int m_RendererID;
public:
	//size：大小
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

};