#version 330 core

precision mediump float;

in vec3 vColor;
out vec4 color;

void main() {
	float s = (1.0 - length((vec2(0.5, 0.5) - gl_PointCoord) * 2.0));
	color = vec4(vColor, s > 0.0 ? 1.0 : 0.0);
}
