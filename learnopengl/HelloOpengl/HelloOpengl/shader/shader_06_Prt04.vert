#version 330 core
layout (location = 0) in vec3 aPos;
//以下输出给片段着色器
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;

void main()
{
    //位置,默认的属性
    gl_Position = vec4(aPos, 1.0);
    //颜色
    ourColor = aColor;
    //纹理
    TexCoord = aTexCoord;
}