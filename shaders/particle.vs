#version 330

layout(location = 0) in vec2 aPosition;
layout(location = 1) in vec3 aColor;

out vec3 vColor;

void main() {
	vColor = aColor;
	gl_PointSize = 3.0;
	gl_Position = vec4(aPosition, 0.0, 1.0);
}
