#ifdef LY_EP03_
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

int main(void)
{
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

	//4.6.0 Compatibility Profile Context 23.19.12.02.240618
	std::cout << glGetString(GL_VERSION) << std::endl;

	/* Loop until the user closes the window */
   //在while中添加代码
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		//===绘制三角形===
		glBegin(GL_TRIANGLES);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(0.0f, 0.5f);
		glVertex2f(0.5f, -0.5f);
		glEnd();
		//===绘制三角形===

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

#endif