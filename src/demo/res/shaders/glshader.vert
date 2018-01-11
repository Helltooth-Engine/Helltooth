#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;

out vec2 uvs;

uniform Vertex {
	mat4 projectionMatrix;
	mat4 viewMatrix;
	mat4 modelMatrix;
};

void main() {
	uvs = uv;
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0);
}