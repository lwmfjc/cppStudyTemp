#ifdef abcd123
#include "Texture.h"
#include "Renderer.h"

#include "vendor/stb_image/stb_image.h"

Texture::Texture(const std::string& path)
	:m_RendererID(0), m_FilePath(path), m_LocalBuffer(nullptr),
	m_Width(0), m_Height(0), m_BPP(0)
{
	stbi_set_flip_vertically_on_load(1);
	//BPP (Bits Per Pixel)。这里它会告诉你图片原本有多少个通道（比如 JPG 是 3 个，带透明的 PNG 是 4 个）
	//4	强制通道数	最关键的参数。你告诉 stbi：“不管原图是啥样，请通通给我转成 RGBA（4 通道）格式”。
	m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);

	//生成一个缓冲区并绑定到某个id
	glGenTextures(1, &m_RendererID);
	//绑定到这个缓冲区id
	glBindTexture(GL_TEXTURE_2D, m_RendererID);
	
	//设置如何处理纹理边界
	//GL_LINEAR：查看目标像素周围的 4 个像素，取它们的加权平均值
	//GL_NEAREST：只取离目标像素最近的那个像素的值
	//GL_TEXTURE_MIN_FILTER：当纹理被缩小的时候，OpenGL 如何采样纹理
	//GL_TEXTURE_MAG_FILTER：当纹理被放大时，OpenGL 如何采样纹理
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//当你的纹理坐标（UV 坐标）超出了  0.0 ~ 1.0  这个“标准范围”时，GPU 应该如何处理那些“多出来”的区域
	//GL_CLAMP：当纹理坐标超出标准范围时，GPU 会将纹理坐标限制在 0.0 ~ 1.0 的范围内，并使用边界像素的颜色进行填充。这意味着如果纹理坐标超出范围，GPU 会==重复使用边界像素==的颜色来填充超出部分。
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	//把这里读到的数据给opengl
	//参数1：GL_TEXTURE_2D：目标类型。告诉 OpenGL 你现在要填充的是一张普通的 2D 纹理。
	//参数2：0：Mipmap 层级(Level)。0 代表原始分辨率（最高级）。如果你以后手动生成多级渐远纹理，这里会用到 1, 2, 3 等。
	//参数3：GL_RGBA8：内部格式(Internal Format)。告诉 OpenGL 你想要在 GPU 内部以什么格式存储这张纹理。GL_RGBA8 表示每个像素使用 4 个字节（32 位）来存储 RGBA 数据。
	//参数4：m_Width：纹理的宽度，以像素为单位。
	//参数5：m_Height：纹理的高度，以像素为单位。
	//参数6：0：边框 (Border)。这是一个遗留参数，在现代 OpenGL 中必须传 0。
	//参数7：GL_RGBA：数据格式。告诉 OpenGL 你提供的数据是 RGBA 格式。
	//参数8：GL_UNSIGNED_BYTE：数据类型。告诉 OpenGL 你提供的数据是无符号字节类型。
	//参数9：m_LocalBuffer：实际的像素数据。
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);

	//传给GPU数据后，解绑Texture
	glBindTexture(GL_TEXTURE_2D, 0);

	if (m_LocalBuffer)
	{
		//stbi_image_free 本质上是一个包装过的 free() 函数。
		stbi_image_free(m_LocalBuffer);
	}

}

Texture::~Texture()
{
	//通知GPU销毁指定的纹理资源，并回收那块显存。
	glDeleteTextures(1, &m_RendererID);
}

void Texture::Bind(unsigned int slot /*= 0*/) const
{
	//激活纹理单元
	//激活纹理单元后，后续的 glBindTexture 调用会将该纹理绑定到当前激活的纹理单元。纹理单元 GL\_TEXTURE0 默认始终处于激活状态
	glActiveTexture(GL_TEXTURE0 + slot);
	//绑定到这个缓冲区id 
	glBindTexture(GL_TEXTURE_2D, m_RendererID);

}

void Texture::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

#endif