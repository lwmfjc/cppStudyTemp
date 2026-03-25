#ifdef LY_EP13
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>
#include <string>

//_debugbreak() 是msvc特有的
//__FILE__和__LINE__ 是所有编译器都支持的
//#x：字符串化操作符。它会将你传入的代码直接转成字符串
//__FILE__ 和 __LINE__：编译器内置宏，自动获取当前代码所在的文件名和行号
#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x,__FILE__,__LINE__));

static void GLClearError()
{
	//直到不是GL_NO_ERROR，就退出while循环
	while (glGetError() != GL_NO_ERROR);
}

static bool GLLogCall(const char* function,
	const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error](" << error << "): "
			<< function << " " << file << ":" << line << std::endl;
		return false;
	}

	return true;
}

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

static ShaderProgramSource ParseShader(const std::string& filepath)
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
static unsigned int CompileShader(unsigned int type,
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

static unsigned int CreateShader(const std::string& vertexShader,
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

int main(void)
{
#pragma region 一些初始化
	GLFWwindow* window;
	// 初始化 GLFW 库，失败则退出
	if (!glfwInit())
		return -1;

	//强制指定使用 Core Profile（核心模式），如果
	//没有手动写着色器则不会渲染；如果不是核心模式，
	//在固定管线中默认颜色是白色，且默认顶点在NDC标准
	//设备坐标系中
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//这是兼容配置模式,会让VAO0成为默认对象
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// 创建窗口对象
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		// 创建失败则清理并退出
		glfwTerminate();
		return -1;
	}

	// 将当前窗口的上下文设置为 OpenGL 渲染的目标
	glfwMakeContextCurrent(window);

	glfwSwapInterval(2);

	// 初始化 GLEW 以加载 OpenGL 函数指针，需在有上下文后执行
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Error!" << std::endl;
	}

#pragma endregion

	// 定义三角形的顶点坐标（CPU 内存）
	float positions[] = {
		-0.5f, -0.5f,//0
		0.5f, -0.5f,//1
		0.5f, 0.5f,//2

		//0.5f, 0.5f,
		-0.5f, 0.5f,//3
		//-0.5f, -0.5f,
	};

	//
	unsigned int indices[] = {
		0,1,2,
		2,3,0
	};

	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);//绑定vao

	unsigned int buffer;
	// 生成一个缓冲区 ID
	glGenBuffers(1, &buffer);
	// 绑定该 ID 到顶点缓冲区插槽
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	// 将顶点数据从 CPU 内存拷贝到 GPU 显存，设为静态读取模式
	glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float),
		positions, GL_STATIC_DRAW);


	// 启用索引为 0 的(顶点)属性 
	glEnableVertexAttribArray(0);
	//1. 打标签：它把当前 GL_ARRAY_BUFFER 里的数据流，贴上了“0号”的标签。2. 定规则：它告诉 GPU，当你（Shader）想要 location = 0 的数据时，请按照“每 2 个 float 为一组”的规则去缓存里抓取。
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (const void*)0);

	//索引缓冲区：index buffer object
	unsigned int ibo;
	// 生成一个缓冲区 ID
	glGenBuffers(1, &ibo);
	// 绑定该 ID 到元素数组缓冲区 (Element Array Buffer)插槽，
	//也称索引缓冲区对象
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	// 将顶点数据从 CPU 内存拷贝到 GPU 显存，设为静态读取模式
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int),
		indices, GL_STATIC_DRAW);

	//这是一个相对路径，相对于 工作目录
	//如果不是在visual studio中运行，就会相对于 可执行文件 所在的目录
	//如果在visual studio中，工作目录被设置为$(ProjectDir) (右键目录-属性-调试-woking directory)
	ShaderProgramSource source = ParseShader("res/shaders/Basic.shader");

	//std::cout << source.VertexSource << std::endl;
	//std::cout << source.FragmentSource << std::endl;

	// 将字符串源码编译并链接成一个完整的程序对象
	unsigned int program = CreateShader(source.VertexSource, source.FragmentSource);
	// 告诉 OpenGL 状态机：接下来的所有绘制指令（如 glDrawArrays）都请使用这个编译好的着色器程序
	// 进行渲染
	glUseProgram(program);


	//===这里故意把他解绑了（假设他去绑定别的去了）===
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glUseProgram(0);
	glBindVertexArray(0);//解绑vao
	//element_array_buffer 和vertexAttribArray不能
	//在解绑vao之前处理，否则就记录进去了
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	//========================================

	float r = 0.0f;
	float increment = 0.05f;

	// 游戏/渲染主循环
	while (!glfwWindowShouldClose(window))
	{
		// 清理屏幕颜色缓冲区
		glClear(GL_COLOR_BUFFER_BIT);

		//绘图前重新绑定
		glUseProgram(program);

		//必须先绑定program，因为vao不负责着色器程序的切换
		glBindVertexArray(vao);


		//glVertexAttribPointer更具体地指明了属性0、属性1，到绑定到当时的GL_ARRAY_BUFFER上的buffer去找，以及如何找。所以这里并不需要重新绑定GL_ARRAY_BUFFER
		//glBindBuffer(GL_ARRAY_BUFFER, buffer);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

		// 读取当前绑定的缓冲区数据并绘制三角形：从
		// 索引0即第1个顶点开始画，读取三个顶点(
		//并行地读第1个顶点的0号属性_以及_第1个顶点的1号属性) 
		//GL_TRIANGLES：这是你告诉 GPU 的拓扑模式（Topology）。它告诉 GPU：“请每 3 个点一组，把它们连成一个三角形。”
		//6：“从我指定的起点开始，连续读取 6 个顶点 的数据。GPU 并不认识“矩形”，它只认识你给的拓扑模式。如果你给 GL_TRIANGLES 模式并传了 6 个点，它会自动执行6\3=2，从而在屏幕上画出2个三角形。
		//glDrawArrays(GL_TRIANGLES, 0, 6);

		//========设置uniform========
		//==在绑定程序后，获取变量地址，然后设置变量==
		//问着色器，让着色器告诉CPU变量的位置
		unsigned int location = glGetUniformLocation(program, "u_Color");
		//不为1时会报错并且停止程序（当设置了变量但是着色器没
		//使用过时，OpenGL会在编译时删除那个变量）
		ASSERT(location != -1);

		if (r > 1.0f)
			increment = -0.05f;
		else if (r < 0.0f)
			increment = 0.05f;

		r += increment;

		//在u_Color的位置上设置数值
		glUniform4f(location, r, 0.3f, 0.0f, 1.0f);
		//========设置uniform========

		//重新启动属性
		//glEnableVertexAttribArray(0);
		//glEnableVertexAttribArray(1);

		//最后一个参数：nullptr (或 0)：表示从绑定的 EBO 数据最开头（偏移量为 0）开始读取索引。	非零值：表示从 EBO 的第几个字节开始读取。
		//glDrawElements 的规范（Specification）中明确规定，第三个参数 type 必须是以下三个之一：	GL_UNSIGNED_BYTE，GL_UNSIGNED_SHORT，GL_UNSIGNED_INT，否则会黑屏
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		//GLClearError();
		//参数错误
		GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

		//ASSERT(GLLogCall());
		//跳过前三个顶点
		//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(3 * sizeof(unsigned int)));

		// 交换前后缓冲区以刷新画面
		glfwSwapBuffers(window);

		// 轮询并处理窗口事件（如键盘输入、关闭动作）
		glfwPollEvents();
	}

	//最后解绑vao
	glBindVertexArray(0);

	// 手动通知显卡驱动释放该程序占用的显存
	glDeleteProgram(program);

	// 退出前清理资源
	glfwTerminate();
	return 0;
}

#endif