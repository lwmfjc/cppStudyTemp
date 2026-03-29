#ifdef LY_EP13
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "Render.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"


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

		VertexArray va;

		//申请创建一个GPU上的缓冲区，绑定并复制进去数据构造函
		//数中已经绑定了，这样glVertexAttribPointer才有效果
		VertexBuffer vb(positions, 4 * 2 * sizeof(float));

		VertexBufferLayout layout;
		layout.Push<float>(2); 
		va.AddBuffer(vb, layout);

		//申请创建一个GPU上的缓冲区，绑定并复制进去数据
		IndexBuffer ib(indices, 6);

		Shader shader("res/shaders/Basic.shader");
		shader.Bind();

		shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);


		//===这里故意把他解绑了（假设他去绑定别的去了）===
		vb.Unbind();

		shader.Unbind();
		va.Unbind();

		//element_array_buffer 和vertexAttribArray不能
		//在解绑vao之前处理，否则就记录进去了
		ib.Unbind();

		//========================================

		float r = 0.0f;
		float increment = 0.05f;

		// 游戏/渲染主循环
		while (!glfwWindowShouldClose(window))
		{
			// 清理屏幕颜色缓冲区
			glClear(GL_COLOR_BUFFER_BIT);

			//绘图前重新绑定
			shader.Bind();

			//必须先绑定program，因为vao不负责着色器程序的切换
			va.Bind();

			if (r > 1.0f)
				increment = -0.05f;
			else if (r < 0.0f)
				increment = 0.05f;

			r += increment;

			//在u_Color的位置上设置数值
			shader.SetUniform4f("u_Color", r, 0.3f, 0.0f, 1.0f);
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
		//glBindVertexArray(0);
	}

	// 退出前清理资源
	//glfwTerminate会破坏Context，导致析构函数中的glGetError()
	//返回一个OpenGL错误
	glfwTerminate();
	return 0;
}

#endif