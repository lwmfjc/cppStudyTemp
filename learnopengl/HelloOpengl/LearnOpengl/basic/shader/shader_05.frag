#version 330 core
out vec4 FragColor;  
in vec3 ourColor;//用同名的ourColor接收顶点着色器给的变量
  
void main()
{
    FragColor = vec4(ourColor, 1.0);
}