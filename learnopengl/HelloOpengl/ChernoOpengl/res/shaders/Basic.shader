#shader vertex
#version 330 core
layout(location = 0 ) in vec4 position;
layout(location = 1 ) in vec2 texCoord;

out vec2 v_TextCoord;
void main()
{
  gl_Position=position;//自动转换，X, Y, Z：如果缺省，默认补 0.0。W：如果缺省，默认补 1.0
  v_TextCoord=texCoord;//从顶点着色器获取到的又传出来
}


#shader fragment
#version 330 core
//layout(location = 0 ) out vec4 color; //这里应该不需要指定layout
out vec4 color; 

in vec2 v_TextCoord;

uniform vec4 u_Color;//同意u_开头表示uniform变量
uniform sampler2D u_Texture;//目前给了2

void main()
{
  //color=vec4(0.2,0.3,0.8,1.0);
  //对待定纹理坐标进行采样
  //u_Texture: 去 u_Texture 号纹理单元（GL_TEXTURE_N） 找那张已经绑好的图片。
  //v_TextCoord: 纹理坐标，告诉 GPU 从图片的哪个位置采样
  vec4 textColor = texture(u_Texture, v_TextCoord);
  //color=u_Color;
 color=textColor;//只要纹理颜色 
  //color=u_Color;//只要纹理颜色 

}
