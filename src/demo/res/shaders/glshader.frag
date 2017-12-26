#version 330 core

in vec4 positions;

layout (location = 0) out vec4 color;

void main() {
	color = positions;
}