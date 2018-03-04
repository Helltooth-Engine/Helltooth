#htshader fragment
#htversion 330 core

layout {
	vec4 color;
};

in {
	vec2 uvs;
};

uniform {
	Texture2D textures[2];
};

main_block {
	color = sample2D(textures[0], uvs);
};