#ifdef LY_EP04_
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

int main(void)
{
#pragma region 一些初始化
	GLFWwindow* window;
	/* Initialize the library */
	if (!glfwInit())
		return -1;
	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	//先有窗口和上下文，加载器才能工作
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Error!" << std::endl;
	}
#pragma endregion


	float positions[6] = {
		-0.5f, -0.5,
		0.0f, 0.5f,
		0.5f, -0.5f
	};

	//用来存储生成的顶点缓冲区id
	unsigned int buffer;
	//定义顶点缓冲区，把生成的缓冲区id(唯一的id)存储到给定地址,
	//之后想使用这个缓冲区对象的时候，传这个id即可
	glGenBuffers(1, &buffer);
	// 告诉 OpenGL：把 ID 为 buffer 的这个缓冲区，
	// “插”进 GL_ARRAY_BUFFER 这个槽位里。
	// 接下来所有针对 GL_ARRAY_BUFFER 的操作（如填
	// 充数据、设置格式），都会作用在这个特定的 buffer 上。
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	//对这个槽位操作：填充数据
	//你告诉显卡：“我打算怎么用这块数据，多久改一次？”显卡会根据你的回答，决定把这块数据放在显存的哪个位置（是读写最快的地方，还是稍微慢一点但方便修改的地方）
	//STREAM: 数据几乎每一帧都要修改（例如：每帧都在变的粒子效果）。STATIC: 数据只设置一次，之后几乎不动（例如：静态的地形、房屋模型）。DYNAMIC : 数据会频繁修改，但可能不像每帧那么夸张
	//DRAW: 数据由 CPU 写入，供 GPU 读取用于画图（这是 99% 的情况）。READ: 数据由 GPU 写入，供 CPU 读取（例如：回传渲染结果）。COPY : 数据由 GPU 写入，供 GPU 以后自己读取。
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float),
		positions, GL_STATIC_DRAW);
	//接下来需要告诉GPU，我给的这几个字节的数据该如何读

	/* Loop until the user closes the window */
	//在while中添加代码
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		//给缓冲区发出指令，1：指定绘制的图形
		//2：指定偏移量（指定数组中起始位置，可以非零）
		//3：渲染的顶点的数量，而不是画多少个“形状”
		// 
		// 关键逻辑：由于 OpenGL 是状态机，该函数会自动去读取当前绑定在GL_ARRAY_BUFFER 上的数据，并参考 glVertexAttribPointer 设置的“说明书”来解析。
		// 注意：在调用此函数时，对应的 VAO（或当前的 VBO 及属性配置）必须处于绑定/启用状态。
		glDrawArrays(GL_TRIANGLES, 0, 3);

		//有个参数填写要绘制的顶点数量
		//另一个参数指定渲染的顶点顺序
		//glDrawElements(...);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

#endif