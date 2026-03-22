#ifdef LY_EP03_
#include <glad/glad.h>
#include <GLFW/glfw3.h> 

#include <iostream>
#include <thread> // 包含 sleep_for
#include <chrono> // 包含时间单位

void processInput(GLFWwindow* window)
{
	/*
	检查用户是否按下了 Esc 键（如果没有按下，glfwGetKey 返回 GLFW\_RELEASE ）。如果用户按下了 Esc 键，我们使用 glfwSetwindowShouldClose 将 GLFW 的 WindowShouldClose 属性设置为 `true` 来关闭 GLFW
	*/
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}


//该函数在窗口大小变化时回调，每当窗口大小发生变化时，GLFW 都会调用此函数并填充相应的参数供您处理
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	//告诉 OpenGL 渲染窗口的大小
	glViewport(0, 0, width, height);
}

int main()
{
	// 1. 初始化 GLFW
	glfwInit();
	//将主版本号和次版本号都设置为 `3` 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	//显式使用核心配置文件。使用核心配置文件意味着我们将获得 OpenGL 功能的一个较小子集，而不会使用我们不再需要的向后兼容功能。
	//强制现代性：如果你不小心写了任何旧时代的函数（比如 glBegin），程序会直接报错或崩溃，而不是默默地运行。这能强制你养成正确的现代绘图习惯。

	//1. 删掉的是：那些由驱动程序自动帮你完成、但性能低下的“黑盒”功能。
	//2. 保留的是：那些能直接操作 GPU 硬件、让性能起飞的核心指令。
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//在 macOS 系统上需要额外添加这行才能生效
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);


	// 2. 创建窗口对象
	//创建一个窗口对象。这个窗口对象保存了所有窗口数据，GLFW 的大多数其他函数都需要用到它。
	//窗口 (Window)：是由操作系统（Windows / macOS）管理的容器。它有标题栏、最小化按钮、边框。
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	//真正存储 OpenGL 所有状态（比如我们之前聊的那个巨大的 struct OpenGL_Context）的，是隐藏在窗口背后的 上下文（Context）
	//告诉 GLFW 将窗口的上下文设置为当前线程的主上下文
	glfwMakeContextCurrent(window);


	//调用任何 OpenGL 函数之前初始化 GLAD
	//glfwGetProcAddress（获取函数地址）,属于 GLFW 库
	//gladLoadGLLoader(...)：属于 GLAD 库。
	//向 GLAD 传递一个函数，用于加载 OpenGL 函数指针的地址，该地址与操作系统相关
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	const GLubyte* renderer = glGetString(GL_RENDERER); // 获取显卡名称
	const GLubyte* version = glGetString(GL_VERSION);   // 获取 OpenGL 版本
	std::cout << "Renderer: " << renderer << std::endl;
	std::cout << "OpenGL version supported: " << version << std::endl;
	//Renderer: AMD Radeon(TM) Vega 8 Graphics
	//OpenGL version supported : 3.3.0 Core Profile Context 23.19.12.02.240618

	//视口 (Viewport)：是 OpenGL 实际绘图的区域。它存在于窗口内部。
	//重点：视口不一定要填满整个窗口。
	//glViewport(0, 0, 800, 600);

	// 注册 窗口大小改变的回调
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	int i = 0;

	//1. 问：该下班（关窗口）了吗？
	while (!glfwWindowShouldClose(window))
	{//顺序原则：先取样（Poll），再处理（Input），后绘制（Render），末提交（Swap）

		//check and call events
		//这个函数负责处理所有的互动
		//它去操作系统那里询问：“刚才这 0.01 秒里，用户动鼠标了吗？按 ESC 键了吗；如果你之前注册过“按下 ESC 就关窗口”的函数，glfwPollEvents 发现你按了 ESC，就会立刻跳过去执行你的那个函数
		// 1. 查：刚才用户有没有搞什么小动作（按键、移动鼠标）？
		glfwPollEvents();


		//input
		//2.算：根据输入处理逻辑（Process Input / Update Logic）
		processInput(window);

		//这里稍微改下逻辑，验证了确实是双缓冲区处理图像
		if (i % 2 == 0)
		{
			i++;
			// 3. 画：清屏并执行渲染指令（Rendering）
			// 这里通常会写 glClear() 和 glDraw... (开始在“后台”画画)
			// rendering commands here
			//设置rgba值，20% 的红，30% 的绿，30% 的蓝，100%不透明
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		}
		else
		{
			i--;
			//设置rgba值，30% 的红，20% 的绿，10% 的蓝，100%不透明
			glClearColor(0.3f, 0.2f, 0.1f, 1.0f);

		}

		//立刻把 GL_COLOR_BUFFER_BIT（颜色缓冲区）里所有的像素，全部涂成我刚才在 glClearColor 里指定的颜色
		glClear(GL_COLOR_BUFFER_BIT);

		//swap the buffers
		/*
	*单缓冲（坏处）：如果你直接在观众面前画，观众会看到你先
	  画背景，再画人物，最后上色。这在屏幕上会导致严重的闪烁，因为观众看到了“半成品”。
	* 双缓冲（glfwSwapBuffers）：
		* 后缓冲区 (Back Buffer)：这是隐藏在后台的画布。所
		  有的 glClear、glDraw... 都在这里偷偷进行。观众看不见。
		* 前缓冲区 (Front Buffer)：这是目前正在屏幕上显示的成品图。
		* glfwSwapBuffers 的动作：当你在后台画好了完整的一帧，这行代码会瞬间把“前台”和“后台”交换。观众看的是上一秒画好的，而你已经在准备下一秒的了。
*/
// 4. 喊：画好了！把画完的后台画布翻到前台给用户看！
		glfwSwapBuffers(window);

	}

	//渲染循环结束后，我们需要彻底清理 / 删除所有已分配的 GLFW 资源
	glfwTerminate();
	return 0;
}

#endif