#shader vertex
#version 330 core
layout(location = 0 ) in vec4 position;
void main()
{
  gl_Position=position;//自动转换，X, Y, Z：如果缺省，默认补 0.0。W：如果缺省，默认补 1.0
}


#shader fragment
#version 330 core
layout(location = 0 ) out vec4 color; //这里应该不需要指定layout
void main()
{
  color=vec4(0.2,0.3,0.8,1.0);
}
