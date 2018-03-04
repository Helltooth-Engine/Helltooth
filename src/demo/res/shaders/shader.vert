#htshader vertex
#htversion 330 core

layout {
	vec3 POSITION as position;
	vec2 UV as uv;
	vec3 NORMAL as normals;
};

uniform {
	mat4 projectionMatrix;
	mat4 viewMatrix;
	mat4 modelMatrix;
};


out {
	vec2 uvs;
};

main_block {

	OUT_POSITION = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0);

	uvs = uv;
};