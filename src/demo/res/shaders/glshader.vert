#version 330 core

layout (location = 0) in vec2 position;

out vec4 positions;

void main() {
	positions = vec4(position, 0.0, 1.0);
	gl_Position = vec4(positions);
}