#pragma once
#include "VertexBuffer.h" 
//#include "VertexBufferLayout.h"

//向前声明
//它告诉编译器：“哥们，后面会有一个类叫 VertexBufferLayout，我现在先提一嘴，你先别管它长啥样，只要知道它是个‘类’就行。”
class VertexBufferLayout;

class VertexArray
{
private:
	unsigned int m_RendererID;
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

	void Bind() const;
	void Unbind() const;
};
