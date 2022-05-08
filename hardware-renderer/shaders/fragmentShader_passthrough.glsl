#version 330 core

layout(location=0) out vec4 fragmentColor;
in vec3 vertex_color;
in vec3 light_dir;
in vec3 normal;

void main(void)
{
  // fragmentColor = normal;
  fragmentColor = vec4(vertex_color * max(dot(normal, light_dir), 0.f), 1.f);
}