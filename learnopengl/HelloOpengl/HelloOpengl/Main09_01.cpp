#ifdef LY_EP09_
#include <glad/glad.h>
#include <GLFW/glfw3.h> 
#include "Shader_05.h"
#include "stb_image.h"
#include <iostream> 

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp" 

static int SCR_WIDTH = 800;
static int SCR_HEIGHT = 600;

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
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
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

	Shader ourShader("shader/shader_08.vs", "shader/shader_08.fs");

	//=========生成纹理==========
	unsigned int texture1;
	//参数1：要生成的纹理数量
	//参数2：创建一个纹理并存储在texture中
	glGenTextures(1, &texture1);

	//绑定，让后续的纹理命令都配置的是当前绑定的纹理
	//只需在调用 glDrawElements 之前绑定纹理，它就会自动将纹理分配给片段着色器的采样器
	//如果没有额外指定，OpenGL 默认你会把这张图插在 0号插槽（GL_TEXTURE0）,我的理解就是他帮你写了glActiveTexture(GL_TEXTURE0);
	//激活纹理单元1，后续的调用会把纹理绑定到当前激活的单元
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);//水平方向平铺
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);//垂直方向平铺
	//渲染过程中切换 mipmap 层级
	//当纹理向下缩放是，选择GL_LINEAR_MIPMAP_LINEAR：在两个最接近的 mipmap 之间进行线性插值，并通过线性插值对插值级别进行采样
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	//当纹理向上缩放选择线性过滤
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;

	//数据读取：OpenGL 从图片的第一行像素数据开始读。对应关系：它认为这第一行数据应该是“最底部”的内容（因为在它的坐标系里，$y = 0$ 是底部）。结果：但实际上，图片数据的第一行是图片的“最顶部”。
	//在加载图片时翻转，加载的时候把数据上下倒过来
	stbi_set_flip_vertically_on_load(true);

	//加载图片， 把图片读进 CPU 内存
	unsigned char* data = stbi_load("textures/container.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		//使用前面加载的图片生成纹理
		//参数1：此操作将在当前绑定的纹理对象上生成同一目标的纹理（因此绑定到目标 GL\_TEXTURE\_1D 或 GL\_TEXTURE\_3D 的任何纹理都不会受到影响）
		//参数2：创建纹理的 mipmap 级别，这里是0
		//参数3：告诉 OpenGL 我们希望以何种格式存储纹理，以rgb值存储
		//参数4、5：生成的纹理的宽度和高度
		//参数6：始终为零，历史遗留问题
		//参数7、8：指定源图像的格式和数据类型（加载图像时使用了 `RGB` 值，并将其存储为 `char` （字节））
		//参数9：实际的图像数据（对应了上面的，是个char字节类型）
		//把图片从 CPU 内存 拷贝到 显存 里的纹理对象中，指的是texture对应的那块内存？
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		//以上只加载了纹理图像的基础层，如果要使用mipmap，就不断递加第二个参数，或者接下来调用生成纹理后调用glGenerateMipmap
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	//生成纹理及其对应的 mipmap 后，最好释放stbi_load加载的内存
	stbi_image_free(data);
	//解绑纹理，“防止误操作”导致的全局状态污染，
	// GL_TEXTURE_2D 就像是一个全局唯一的插槽
	//glBindTexture(GL_TEXTURE_2D, 0);


	unsigned int texture2;
	//参数1：要生成的纹理数量
	//参数2：创建一个纹理并存储在texture中
	glGenTextures(1, &texture2);

	//绑定，让后续的纹理命令都配置的是当前绑定的纹理
	//只需在调用 glDrawElements 之前绑定纹理，它就会自动将纹理分配给片段着色器的采样器
	//如果没有额外指定，OpenGL 默认你会把这张图插在 0号插槽（GL_TEXTURE0）,我的理解就是他帮你写了glActiveTexture(GL_TEXTURE0);
	//激活纹理单元1，后续的调用会把纹理绑定到当前激活的单元
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, texture2);

	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);//水平方向平铺
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);//垂直方向平铺
	//渲染过程中切换 mipmap 层级
	//当纹理向下缩放是，选择GL_LINEAR_MIPMAP_LINEAR：在两个最接近的 mipmap 之间进行线性插值，并通过线性插值对插值级别进行采样
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	//当纹理向上缩放选择线性过滤
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//加载图片， 把图片读进 CPU 内存
	unsigned char* data2 = stbi_load("textures/awesomeface.png", &width, &height, &nrChannels, 0);
	if (data2)
	{
		//使用前面加载的图片生成纹理
		//参数1：此操作将在当前绑定的纹理对象上生成同一目标的纹理（因此绑定到目标 GL\_TEXTURE\_1D 或 GL\_TEXTURE\_3D 的任何纹理都不会受到影响）
		//参数2：创建纹理的 mipmap 级别，这里是0
		//参数3：告诉 OpenGL 我们希望以何种格式存储纹理，以rgb值存储
		//参数4、5：生成的纹理的宽度和高度
		//参数6：始终为零，历史遗留问题
		//参数7、8：指定源图像的格式和数据类型（加载图像时使用了 `RGB` 值，并将其存储为 `char` （字节））
		//参数9：实际的图像数据（对应了上面的，是个char字节类型）
		//把图片从 CPU 内存 拷贝到 显存 里的纹理对象中，指的是texture对应的那块内存？
		//这里是RGBA，填错就不显示了
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);
		//以上只加载了纹理图像的基础层，如果要使用mipmap，就不断递加第二个参数，或者接下来调用生成纹理后调用glGenerateMipmap
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	//生成纹理及其对应的 mipmap 后，最好释放stbi_load加载的内存
	stbi_image_free(data2);
	//解绑纹理，“防止误操作”导致的全局状态污染，
	// GL_TEXTURE_2D 就像是一个全局唯一的插槽
	//glBindTexture(GL_TEXTURE_2D, 0); 


	//=========应用纹理==========

	//=========定点信息包括坐标、颜色、纹理坐标========
	//float vertices[] = {
	//	// positions          // colors           // texture coords
	//	 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
	//	 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right 
	//	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f ,   // top left 

	//	 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
	//	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
	//	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f ,   // top left 

	//}; 
	float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	//创建顶点缓冲区对象，
	//存放顶点属性（位置、颜色、纹理坐标）的大仓库
	unsigned int VBO;
	//找目前没被占用的数字，并把它分配给 VBO
	glGenBuffers(1, &VBO);

	//创建顶点数组对象
	unsigned int VAO;
	//早期设计逻辑中，它代表的是“一组指向顶点数据的状态集合”，
	//管理着一堆顶点属性数组的配置,0号是位置数组的配置,1号是
	//颜色数组的配置,2号是纹理坐标数组的配置。
	//申请的是一个状态容器（就像在显存里买了一个文件夹/档案袋）
	glGenVertexArrays(1, &VAO);

	//激活VAO
	glBindVertexArray(VAO);

	//绑定VBO 
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//顶点数组复制到顶点缓冲区对象
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	//配置位置属性
	//顶点着色器程序编译后，会去0号通道找顶点位置数据画图，结果cpp代码这里没写或者写错了，他就找不到数据
	//它会将当前属性（比如 0 号位置）与当前正绑定在 GL_ARRAY_BUFFER 上的那个 VBO 关联起来 
	//配置的是“如何从当前绑定到 GL_ARRAY_BUFFER 的那个缓冲区（Buffer）读取数据”。
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//配置颜色属性
	/*glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);*/

	//配置纹理属性
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	//这里的2，和上面第一个参数，也就是 vs文件中的location一致，
	//表示要启用 2 号属性（对应纹理）
	glEnableVertexAttribArray(2);

	//关于这个 VBO 的配置已经彻底结束了
	glBindBuffer(GL_ARRAY_BUFFER, 0); // 解绑 VBO 是安全的，VAO 已经记录了它
	glBindVertexArray(0);             // 封存 VAO
	//封存VAO后解绑EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//创建了一个初始坐标为 (1, 0, 0) 的点
	//第四个分量 w = 1.0f 非常关键。在图形学中，如果 $w=1$，它代表一个位置（点）；如果 w=0，它代表一个方向（向量），因为w=0时他和平移矩阵相乘结果为本身，所以说他代表方向。
	//只有 w=1 时，平移矩阵才会对它起作用
	glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);


	//通过单参数构造函数，创建一个对角矩阵
	//因为对角矩阵和任何矩阵S相乘，得到的还是S
	//glm::mat4 trans = glm::mat4(1.0f);
	//绕z轴(0.0,0.0,1.0)旋转90度
	//伸出你的右手。
	//将大拇指指向旋转轴的正方向（在你的代码里是 Z 轴正方向，即指向屏幕外、对着你的脸）。
	//此时，你其余四个手指自然卷曲的方向，就是** 正角度（ + ） * *旋转的方向。
	//原本在 (1, 0, 0) 的点会跑到 (0, 1, 0)。视线中就是逆时针移动了 90 度。	
	 //trans = glm::rotate(trans, glm::radians(90.f), glm::vec3(0.0, 0.0, 1.0));

	//所有方向上都缩放为0.5
	//trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));




	//以线框模式绘制三角形
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


	// 注册 窗口大小改变的回调
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


	//将新创建的程序对象作为参数来激活
	ourShader.use();

	//GPU会去读 GL_TEXTURE1 里的图
	glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 1);
	//GPU会去读 GL_TEXTURE2 里的图
	ourShader.setInt("texture2", 2);
	glEnable(GL_DEPTH_TEST);

	bool hasLog = false;

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

		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// 3. 画：清屏并执行渲染指令（Rendering）
		// 这里通常会写 glClear() 和 glDraw... (开始在“后台”画画)
		// rendering commands here
		//设置rgba值，20% 的红，30% 的绿，30% 的蓝，100%不透明
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

		//立刻把 GL_COLOR_BUFFER_BIT（颜色缓冲区）里所有的像素，全部涂成我刚才在 glClearColor 里指定的颜色
		//glClear(GL_COLOR_BUFFER_BIT);
		//还清楚了深度缓冲区
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



		//因为我前面解绑了，所以这里要再重新绑定
		//glBindTexture(GL_TEXTURE_2D, texture1);
		//glBindTexture(GL_TEXTURE_2D, texture2);
		// 这一行告诉 OpenGL：“把刚才录制好的那个 VAO 档案袋拿出来，
		// 把它里面的所有状态（VBO 是谁、怎么读、开关在哪）一瞬间全部复原到桌面上！”
		glBindVertexArray(VAO);

		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);

		//让相机先向上，再靠近(向前，即-z轴方向)
		//view = glm::translate(view, glm::vec3(0.0f, -0.5f, 2.0f));


		//view = glm::translate(view, glm::vec3(0.8f, 0.0f, 1.0f));



		//===========视野空间处理=========
		//视图空间空间，观察矩阵
		glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
		glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);

		//normalize：归一化，让向量的长度变成1，但是方向不变。把它变成长度为 1 的单位向量后，它就能作为一个标准的轴（Axis）--z轴
		glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);

		//上向量 
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

		//叉积，得到一个垂直于这两个向量的向量
		//叉积（Cross Product）的方向遵循右手定则，伸出右手，平整手掌。四指指向第一个向量：也就是 up）。向第二个向量弯曲四指：也就是 cameraDirection。大拇指的指向：就是叉积的结果 cameraRight
		glm::vec3 cameraRight = glm::normalize(
			glm::cross(up, cameraDirection));

		glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);



		if (!hasLog) {
			std::cout << "Camera Position:  " << cameraPos.x << ", " << cameraPos.y << ", " << cameraPos.z << std::endl;
			std::cout << "Camera Direction: " << cameraDirection.x << ", " << cameraDirection.y << ", " << cameraDirection.z << std::endl;
			std::cout << "Camera Right:     " << cameraRight.x << ", " << cameraRight.y << ", " << cameraRight.z << std::endl;
			std::cout << "Camera Up (Final):" << cameraUp.x << ", " << cameraUp.y << ", " << cameraUp.z << std::endl;
			hasLog = true;

		}

		//glm::mat4 view;
		/*view = glm::lookAt(glm::vec3(-0.5f, 0.3f, 3.0f),
			glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));*/
		view = glm::lookAt(glm::vec3(0.0f, 0.0f,  3.0f),
			glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f, 1.0f, 0.0f));
		/*view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),
			glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));*/


		//view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		ourShader.setMat4("view", view);
		//===========视野空间处理=========


		//如果不用投影，不会处理w，直接就超出了[1.0,1.0]的范围
		//projection= glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);

		//角度是负数会导致y轴方向的坐标全部变为负数，即镜像
		/*projection = glm::perspective(glm::radians(-55.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);*/
		//只看得到z值在-0.1f->-100.f之间的物体
		projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		ourShader.setMat4("projection", projection);


		//对角线都是1.0
		glm::mat4 model = glm::mat4(1.0f);

		//如果是+45度，是上面的顶点朝着z轴正方形(转)
		//model = glm::rotate(model, glm::radians( -45.0f), glm::vec3(1.0f, 0.0f, 0.0f));

		//翻转到90度之后，观察到的 Y坐标正负相反，其实是因为你的正方形翻面了
		//model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));

		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));

		/*float angle = 2.0f * (i + 1);
		//model = glm::rotate(model, (float)glfwGetTime() * angle, //glm::vec3(1.0f, 0.3f, 0.5f));*/
		float angle = 45.0f;// *i;
		model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));

		ourShader.setMat4("model", model);

		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glDrawArrays(GL_TRIANGLES, 0, 36);




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
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);

	//释放所有显存资源
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteTextures(1, &texture1);
	glDeleteTextures(1, &texture2);

	//渲染循环结束后，我们需要彻底清理 / 删除所有已分配的 GLFW 资源
	glfwTerminate();
	return 0;
}

#endif