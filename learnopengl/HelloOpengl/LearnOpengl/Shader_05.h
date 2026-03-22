#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h> // include glad to get all the required OpenGL headers

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp" 

class Shader
{
public:
    // the program ID
    unsigned int ID;

    //自动打开这两个文件，读取里面的代码字符串，然后执行你之前手动写的那一长串：创建着色器 -> 附加源码 -> 编译 -> 链接程序 -> 检查错误
    //读取文件，编译着色器
    Shader(const char* vertexPath, const char* fragmentPath);

    //将新创建的程序对象激活 
    void use();

    //封装了复杂的 glGetUniformLocation 和 glUniform... 系列函数，
    // 查询 uniform 变量的位置并设置其值
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setMat4(const std::string& name, glm::mat4 value) const; 
    
};
#endif