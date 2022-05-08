#version 330 core

// comment
layout(location=0) in vec3 in_position;
layout(location=1) in vec3 in_color;

out vec3 vertex_color;

uniform mat4 projMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

void main(void)
{
  vertex_color = in_color;
  gl_Position = projMatrix * viewMatrix * modelMatrix * vec4(in_position, 1.0);
}








