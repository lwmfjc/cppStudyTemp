#pragma once

//专门处理顶点缓冲区的生成、绑定、解绑及内存释放
class IndexBuffer
{
private:
	//一个相关的渲染器id
	unsigned int m_RendererID;
	unsigned int m_Count;
public:
	//count：个数
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	inline unsigned int GetCount() const { return m_Count; }

};