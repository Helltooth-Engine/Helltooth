#version 330 core

in vec4 positions;

layout (location = 0) out vec4 color;

void main() {
	color = vec4(positions.x + 0.5, positions.y + 0.5, positions.z + 0.5, positions.w);
}