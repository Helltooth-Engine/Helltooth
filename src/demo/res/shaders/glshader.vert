#version 330 core

layout (location = 0) in vec3 position;

out vec4 positions;

uniform Vertex {
	mat4 projectionMatrix;
};

void main() {
	positions = projectionMatrix * vec4(position, 1.0);
	gl_Position = vec4(positions);
}