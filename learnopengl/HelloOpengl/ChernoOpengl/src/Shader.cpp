#pragma once
#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream> 
#include "Render.h"

Shader::Shader(const std::string& filepath)
	:m_FilePath(filepath),m_RendererID(0)
{
	ShaderProgramSource source = ParseShader(filepath);
	m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);

}

Shader::~Shader()
{
	glDeleteProgram(m_RendererID);
}

void Shader::Bind() const
{
	glUseProgram(m_RendererID);
}

void Shader::Unbind() const
{
		glUseProgram(0);
}

 ShaderProgramSource Shader::ParseShader(const std::string& filepath)
{

	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	//input file stream
	std::ifstream stream(filepath);

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;

	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
			{
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos)
			{
				type = ShaderType::FRAGMENT;
			}
		}
		else
		{
			ss[(int)type] << line << '\n';
		}
	}

	return { ss[0].str(),ss[1].str() };

}

//GLenum也就是unsigned int,这里不用GLenum是为了解耦
unsigned int Shader::CompileShader(unsigned int type,
	const std::string& source)
{
	//创建着色器对象，向 OpenGL 申请一个空的“容器”来存放你的代码
	//把光标放在 glCreateShader( 的左括号后面，然后按下 Ctrl + Shift + Space。会弹出一个小黑框，显示：GLuint glCreateShader(GLenum type)
	//到glew.h搜索，发现typedef unsigned int GLenum;
	unsigned int id = glCreateShader(type);
	//返回一个指向该字符串首地址的只读指针（const char*）
	const char* src = source.c_str();

	//有了容器后，你需要把写好的字符串代码塞进去（拷贝）
	//3种用法
	//1. glShaderSource(id, 1, &src, nullptr);	只有一个字符串，且它是以 \0 结尾的。
	//2. glShaderSource(id, 1, &src, &len);	只有一个字符串，长度由 len 指定。
	//3. glShaderSource(id, 2, strings, lengths);	有两个字符串片段（数组形式），长度分别由 lengths[0] 和 lengths[1] 指定。
	glShaderSource(id, 1, &src, nullptr);

	//将你的 GLSL 代码翻译成显卡能理解的机器指令
	glCompileShader(id);

	//错误处理
	int result;

	// 查询编译状态：询问 OpenGL 这个 shader 编译成功了吗？
	// GL_COMPILE_STATUS 会把结果存入 result 中（成功为 GL_TRUE，失败为 GL_FALSE）
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE)
	{
		int length;
		//获取错误日志长度：如果编译失败，先问一下错误信息一共有多少个字符
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		//在栈上申请内存
		//如果申请的内存太大，alloca会导致栈溢出（1MB）
		char* message = (char*)alloca(length * sizeof(char));
		//提取错误信息：把显卡驱动里的具体报错文字拷贝到我们刚才申请的 message 内存中
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile " << ((type == GL_VERTEX_SHADER) ? "vertex" : "fragment") << " shader!";
		std::cout << message << std::endl;
		//清理：编译失败了，这个 shader 对象也就没用了，删掉它防止内存泄漏
		glDeleteShader(id);
		return 0;
	}


	return id;
}


 unsigned int Shader::CreateShader(const std::string& vertexShader,
	const std::string& fragmentShader)
{
	//在 GPU 中申请一个空的“程序对象”
	unsigned int program = glCreateProgram();

	//编译顶点着色器
	unsigned int vs = CompileShader(GL_VERTEX_SHADER,
		vertexShader);
	//编译片段着色器
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER,
		fragmentShader);

	//把已经编译好的顶点着色器和片段着色器附加到程序对象中
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	//链接
	glLinkProgram(program);
	//验证当前的程序是否能在当前的 OpenGL 状态下执行（
	// 检查顶点着色器的输出是否与片段着色器的输入匹配，并
	// 生成最终的可执行二进制代码。）
	glValidateProgram(program);

	//删除临时的中间产物（类似编译完 C++ 后删除 .obj
	glDeleteShader(vs);
	glDeleteShader(fs);


	return program;
}


void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

unsigned int Shader::GetUniformLocation(const std::string& name)
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
	{
		return m_UniformLocationCache[name];
	}
	unsigned int location=glGetUniformLocation(m_RendererID, name.c_str());
	if (location == -1)
		std::cout << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;

	m_UniformLocationCache[name] = location;
	return location;
}
