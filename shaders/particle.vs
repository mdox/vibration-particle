#version 330 core

layout(location = 0) in vec2 aPosition;
layout(location = 1) in vec3 aColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 vColor;

void main() {
	vColor = aColor;
	gl_PointSize = 3.0;
	gl_Position = projection * view * model * vec4(aPosition, 0.0, 1.0);
}
