#version 330 core

in vec2 uvs;

uniform sampler2D textures[2];

layout (location = 0) out vec4 color;

void main() {
	color = texture(textures[0], uvs).zyxw;
}