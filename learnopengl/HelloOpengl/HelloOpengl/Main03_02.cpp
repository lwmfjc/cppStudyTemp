#ifdef LY_EP03_
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

// 回调函数：每当窗口大小改变时，GLFW 都会调用它
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // 确保视口（Viewport）匹配新的窗口尺寸
    glViewport(0, 0, width, height);
}

// 处理所有输入：查询 GLFW 在本帧中是否有相关按键按下/释放
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main()
{
    // 1. 初始化 GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // 2. 创建窗口对象
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL - Env Test", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    // 注册窗口大小改变的回调
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // 3. 初始化 GLAD (在调用任何 OpenGL 函数之前)
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    // 4. 渲染循环
    while (!glfwWindowShouldClose(window))
    {
        // 输入
        processInput(window);

        // 渲染指令
        // 设置清空屏幕所用的颜色（状态设置）
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        // 清除颜色缓冲（状态使用）
        glClear(GL_COLOR_BUFFER_BIT);

        // 检查并调用事件，交换缓冲
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // 5. 释放资源
    glfwTerminate();
    return 0;
}

#endif