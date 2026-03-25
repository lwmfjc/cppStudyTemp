#ifdef LY_EP05_
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

int main(void)
{
#pragma region 一些初始化
	GLFWwindow* window;
	// 初始化 GLFW 库，失败则退出
	if (!glfwInit())
		return -1;

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

	// 初始化 GLEW 以加载 OpenGL 函数指针，需在有上下文后执行
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Error!" << std::endl;
	}
#pragma endregion

	// 定义三角形的顶点坐标（CPU 内存）
	float positions[10] = {
		-0.5f, -0.5,
		0.0f, 0.5f,
		0.5f, -0.5f, 
	};

	unsigned int buffer;
	// 生成一个缓冲区 ID
	glGenBuffers(1, &buffer);
	// 绑定该 ID 到顶点缓冲区插槽
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	// 将顶点数据从 CPU 内存拷贝到 GPU 显存，设为静态读取模式
	glBufferData(GL_ARRAY_BUFFER, 25 * sizeof(float),
		positions, GL_STATIC_DRAW);


	// 启用索引为 0 的(顶点)属性
	// 默认情况下，所有顶点属性都是禁用的，必须手动“合上电闸”才能让 GPU 读取该属性。
	glEnableVertexAttribArray(0);

	//参数1-index：顶点的哪个属性[有位置、颜色、纹理等]（和在着色器程序里指定的索引一致），设置完后，当使用着色器程序从显卡读取位置时，就能从缓冲区，简单的读取并使用这些属性
	//参数2-size：每个属性是几个分量的向量，即占用了几个数值
	//参数3-type：提供的数据类型
	//参数4normalized：是否归一化，可以让cpu帮你做（那就是true），或者弄好传给它。（比如
	//把0-255映射成0-1
	//参数5stride：从*当前顶点的属性的起始点*到*下一个顶点的同属性起始点*的字节数
	//参数6pointer：在单个顶点数据块内，该属性距离(这个块的)起始位置的字节偏移。可以使用宏简化 
	//1. 打标签：它把当前 GL_ARRAY_BUFFER 里的数据流，贴上了“0号”的标签。2. 定规则：它告诉 GPU，当你（Shader）想要 location = 0 的数据时，请按照“每 2 个 float 为一组”的规则去缓存里抓取。
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (const void*)0); 



	// 游戏/渲染主循环
	while (!glfwWindowShouldClose(window))
	{
		// 清理屏幕颜色缓冲区
		glClear(GL_COLOR_BUFFER_BIT);

		// 读取当前绑定的缓冲区数据并绘制三角形：从
		// 索引0即第1个顶点开始画，读取三个顶点(
		//并行地读第1个顶点的0号属性_以及_第1个顶点的1号属性) 
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// 交换前后缓冲区以刷新画面
		glfwSwapBuffers(window);

		// 轮询并处理窗口事件（如键盘输入、关闭动作）
		glfwPollEvents();
	}

	// 退出前清理资源
	glfwTerminate();
	return 0;
}

#endif