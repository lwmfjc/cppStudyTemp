#version 330 core
out vec4 FragColor;
  
in vec3 ourColor;
//对应的纹理坐标
in vec2 TexCoord;
//纹理采样器
uniform sampler2D ourTexture;

void main()
{
    //其实这里ourColor没用的，不过
    //这里给他强行加了奇怪的效果
    //这个不是向量乘积，a * b = (ar* br,ag*bg,ab*bb,aa*ba)
    FragColor = texture(ourTexture, TexCoord) * vec4(ourColor, 1.0);
}