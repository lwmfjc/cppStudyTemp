#include "VertexArray.h"
//这里要真正调用 layout.GetElements()。这时候编译器必须看到具体的类定义，才能知道 GetElements() 函数长什么样。
#include "VertexBufferLayout.h"

VertexArray::VertexArray()
{ 
	glGenVertexArrays(1, &m_RendererID);

}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_RendererID);

}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();
	vb.Bind();
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;
	for (unsigned int i=0;i<elements.size();i++)
	{
		const auto& element = elements[i];
		// 启用索引为 i 的(顶点)属性 
		glEnableVertexAttribArray(i);
		//1. 打标签：它把当前 GL_ARRAY_BUFFER 里的数据流，贴上了“i号”的标签。2. 定规则：它告诉 GPU，当你（Shader）想要 location = 0 的数据时，请按照“每 count 个 float 为一组”的规则去缓存里抓取。
		glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStrde(), (const void*)offset);

		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}

}

void VertexArray::Bind() const
{
	glBindVertexArray(m_RendererID);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);

	//这里是否要禁用呢，但是视频里面没有存count，所以也不知道总共有几个
	/*for (unsigned int i = 0; i < elements.size(); i++)
	{
		glDisableVertexAttribArray(i);
	}*/

}
