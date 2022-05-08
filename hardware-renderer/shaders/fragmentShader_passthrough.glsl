#version 330 core

layout(location=0) out vec4 fragmentColor;
in vec3 vertex_color;

void main(void)
{
  fragmentColor = vec4(vertex_color, 1.0);
}