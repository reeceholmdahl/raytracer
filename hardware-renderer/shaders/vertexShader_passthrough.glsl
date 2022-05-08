#version 330 core

// comment
layout(location=0) in vec3 in_position;
layout(location=1) in vec3 in_normal;

out vec3 vertex_color;
out vec3 light_dir;
out vec3 normal;

uniform mat4 projMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform vec3 modelColor;
uniform vec3 lightPos;

void main(void)
{
  vertex_color = modelColor;
  light_dir = normalize(lightPos - in_position);
  normal = vec3(modelMatrix * vec4(in_normal, 0.f));
  gl_Position = projMatrix * viewMatrix * modelMatrix * vec4(in_position, 1.0);
}








