#ifdef LY_EP05_
#include <glad/glad.h>
#include <GLFW/glfw3.h> 

#include <iostream> 

//GLSL风格代码
const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos; // the position variable has attribute position 0
  
out vec4 vertexColor; // specify a color output to the fragment shader

void main()
{
    gl_Position = vec4(aPos, 1.0); // see how we directly give a vec3 to vec4's constructor
    vertexColor = vec4(0.5, 0.0, 0.0, 1.0); // set the output variable to a dark-red color
}
)";

const char* fragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;
  
in vec4 vertexColor; // the input variable from the vertex shader (same name and same type)  

void main()
{
    FragColor = vertexColor;
}
)";

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


	//=============顶点着色器的编译============= 
	//创建顶点着色器对象，通过ID引用
	unsigned int vertexShader;
	//创建顶点着色器，并将顶点着色器存储
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	//将着色器源代码附加到着色器对象
	//参数1：要编译成的着色器对象
	//参数2：指定要作为源代码传递的字符串数量
	//参数3：顶点着色器的实际源代码
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//编译着色器
	glCompileShader(vertexShader);
	//检查编译是否成功
	int  success;
	char infoLog[512];
	//检查编译是否成功
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		//获取错误信息并打印出来
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//========片段着色器========
	//创建片段着色器对象，通过ID引用
	unsigned int fragmentShader;
	//创建片段着色器对象,并将ID存储
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	//将片段着色器源代码附加到片段着色器对象
	//参数1：要编译成的片段着色器对象
	//参数2：指定要作为源代码传递的字符串数量
	//参数3：片段着色器的实际源代码
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	//检查编译是否成功
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//创建着色器程序对象
	unsigned int shaderProgram;
	//创建一个程序并返回新创建的程序对象的 ID 引用
	shaderProgram = glCreateProgram();

	//将着色器附加到程序上，并通过 glLinkProgram 将它们链接起来
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}


	//着色器对象链接到程序对象后就可以删除它们了
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	//=========输入的顶点存储========
	float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
	};
	//②生成具有缓冲区ID的缓冲区
	unsigned int VBO;
	glGenBuffers(1, &VBO);


	////③将新创建的缓冲区绑定到GL_ARRAY_BUFFER上
	////（对 GL\_ARRAY\_BUFFER 目标）进行的任何缓冲区 *调用* 都将用于配置当前绑定的缓冲区
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	////④进行数组操作
	////glBufferData 函数专门用于将用户定义的数据复制到当前绑定的缓冲区中
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	////参数1：指定位置顶点属性的位置，顶点着色器中我们使用了 layout(lacation=0)
	////参数2：指定顶点属性的大小 3
	////参数3：指定数据类型为 GL\_FLOAT
	////参数4：指定是否要对数据进行归一化
	////参数5：步长，相邻顶点之间的间距
	////参数6：数据(这里指位置)在缓冲区中的起始偏移量
	////告诉 OpenGL 如何解释顶点数据（每个顶点属性）
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);

	//改为使用VAO
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);

	// 第一步：激活 VAO（开始录制）
	glBindVertexArray(VAO);
	// 第二步：绑定 VBO（VAO 记住了：现在这个 VBO 是我的人了）
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 第三步：配置属性（VAO 记住了：VBO 里的数据应该这样读）
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // 解绑 VBO 是安全的，VAO 已经记录了它 
	// 当你写完这些，VAO 内部已经偷偷存好了 VBO 的 ID 和 Pointer 的规则。
	glBindVertexArray(0); // 录制结束，把档案袋封好放回架子上。
	 
	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	//查询有几个可用的顶点属性
	std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl; //我的电脑是32

	// 注册 窗口大小改变的回调
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
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

		// 3. 画：清屏并执行渲染指令（Rendering）
		// 这里通常会写 glClear() 和 glDraw... (开始在“后台”画画)
		// rendering commands here
		//设置rgba值，20% 的红，30% 的绿，30% 的蓝，100%不透明
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

		//立刻把 GL_COLOR_BUFFER_BIT（颜色缓冲区）里所有的像素，全部涂成我刚才在 glClearColor 里指定的颜色
		glClear(GL_COLOR_BUFFER_BIT);

		//将新创建的程序对象作为参数来激活
		glUseProgram(shaderProgram);

		// 这一行告诉 OpenGL：“把刚才录制好的那个 VAO 档案袋拿出来，
		// 把它里面的所有状态（VBO 是谁、怎么读、开关在哪）一瞬间全部复原到桌面上！”
		glBindVertexArray(VAO);
		//绘制对象
		glDrawArrays(GL_TRIANGLES, 0, 3);

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