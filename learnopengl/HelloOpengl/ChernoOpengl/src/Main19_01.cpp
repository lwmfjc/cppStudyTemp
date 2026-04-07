#ifdef LY_EP19
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "Renderer.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"


int main(void)
{
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

		//解决白屏问题1：先创建一个不可见的窗口，清屏并交换缓冲后再显示窗口
		glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

		// 创建窗口对象
		window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
		//验证：创建windows之后马上整个白屏了
		//system("pause");

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
			-0.5f, -0.5f,0.0f,0.0f,//0
			0.5f, -0.5f,1.0f,0.0f,//1
			0.5f, 0.5f,1.0f,1.0f,//2

			//0.5f, 0.5f,
			-0.5f, 0.5f,0.0f,1.0f,//3
			//-0.5f, -0.5f,
		};

		//
		unsigned int indices[] = {
			0,1,2,
			2,3,0
		};

		//默认情况下，OpenGL 是“覆盖”模式。如果一个像素点已经有颜色了（比如背景色），新画上去的像素会直接把旧的顶掉。开启这个开关后，OpenGL 就不再简单地覆盖，而是会把“新颜色”和“旧颜色”按照某种比例混合在一起
		glEnable(GL_BLEND);
		//把要画上去的新颜色称为 源 (Source, 简称 src)，把已经在屏幕上的旧颜色称为 目标 (Destination, 简称 dst)
		//Result = (src x F_src) + (dst x F_dst)
		//F_src表示新颜色的比例，F_dst表示旧颜色的比例。比如 F_src = 0.3，那么GL_ONE_MINUS_SRC_ALPHA时 F_dst = 0.7， GL_SRC_ALPHA时 F_dst = 0.3
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		VertexArray va;

		//申请创建一个GPU上的缓冲区，绑定并复制进去数据构造函
		//数中已经绑定了，这样glVertexAttribPointer才有效果
		VertexBuffer vb(positions, 4 * 4 * sizeof(float));

		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);
		va.AddBuffer(vb, layout);

		//申请创建一个GPU上的缓冲区，绑定并复制进去数据
		IndexBuffer ib(indices, 6);

		//shader.Bind();

		//shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

		//这里绑定了纹理，shader里就能取到
		Texture texture("res/textures/ChernoLog.png");
		texture.Bind(2);//默认绑定0

		//===这里故意把他解绑了（假设他去绑定别的去了）===
		vb.Unbind();

		//shader.Unbind();
		va.Unbind();

		//element_array_buffer 和vertexAttribArray不能
		//在解绑vao之前处理，否则就记录进去了
		ib.Unbind();

		//========================================

		float r = 0.0f;
		float increment = 0.05f;

		Renderer renderer;
		Shader shader("res/shaders/Basic.shader");
		shader.Bind();
		shader.SetUniform1i("u_Texture", 2);

		//解决白屏问题2：在进入 while 循环前，手动清一次屏并交换缓冲
		//设置“清除颜色”
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		//用上面选好的“油漆”填满整个颜色缓冲区（Color Buffer）
		glClear(GL_COLOR_BUFFER_BIT);
		//交换缓冲区
		glfwSwapBuffers(window); // 这一步把“深绿色”推送到显卡
		//解决白屏问题3：最后才显示窗口
		glfwShowWindow(window);

		// 游戏/渲染主循环
		while (!glfwWindowShouldClose(window))
		{
			// 清理屏幕颜色缓冲区
			renderer.Clear();


			//必须先绑定program，因为vao不负责着色器程序的切换
			//va.Bind();

			if (r > 1.0f)
				increment = -0.05f;
			else if (r < 0.0f)
				increment = 0.05f;

			r += increment;

			//绘图前重新绑定
			shader.Bind();
			//在u_Color的位置上设置数值
			shader.SetUniform4f("u_Color", r, 0.3f, 0.0f, 1.0f);
			//========设置uniform========

			renderer.Draw(va, ib, shader);


			// 交换前后缓冲区以刷新画面
			glfwSwapBuffers(window);

			// 轮询并处理窗口事件（如键盘输入、关闭动作）
			glfwPollEvents();
		}

		//最后解绑vao
		//glBindVertexArray(0);
	}

	// 退出前清理资源
	//glfwTerminate会破坏Context，导致析构函数中的glGetError()
	//返回一个OpenGL错误
	glfwTerminate();
	return 0;
}

#endif