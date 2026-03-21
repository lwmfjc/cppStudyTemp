#version 330 core
out vec4 FragColor;
  
in vec3 ourColor;
//对应的纹理坐标
in vec2 TexCoord;

//所有的 Uniform 变量在初始化时默认值都是 0
//纹理采样器
uniform sampler2D ourTexture;
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    //其实这里ourColor没用的，不过
    //这里给他强行加了奇怪的效果
    //这个不是向量乘积，a * b = (ar* br,ag*bg,ab*bb,aa*ba)
    //FragColor = texture(ourTexture, TexCoord) * vec4(ourColor, 1.0);
    //颜色是片段着色器拿着这个纹理坐标去纹理采样器查的。”
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
    //FragColor = mix(texture(texture1, TexCoord), texture(texture2, vec2(-TexCoord.s,TexCoord.t)), 0.2);

}