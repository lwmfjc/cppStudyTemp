#pragma once
#include <string>
class Texture
{
private:
	unsigned int m_RendererID;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;

	//BPP：它告诉 OpenGL 每一个像素到底由多少个数字组成。如果是 4，OpenGL 就知道按 [R, G, B, A] 的格式去解析数据
	int m_Width, m_Height, m_BPP; //BPP:每像素位数

public:
	Texture(const std::string& path);
	~Texture();
	//想要绑定纹理的插槽
	//一次性可以绑定多个纹理，Windows上可能有32个，取决于显卡
	void Bind(unsigned int slot = 0) const;
	void Unbind() const;
	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }
};