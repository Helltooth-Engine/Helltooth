#include <iostream>
#include <Helltooth.hpp>
#include <gl/GL.h>

#include <graphics/shaders/Shader.hpp>

#include "Player.hpp"

using namespace std;
using namespace ht;
using namespace core;
using namespace utils;

int main() {
	Window window(L"Window", 1280, 720);

	VFS::Mount("res", "res/shaders/");

	float positions[] = {
		-.5f, -.5f,
		.5f, -.5f,
		0.0f, .5f
	};


	BufferLayout layout = BufferLayout();
	layout.AddLayout<float>("POSITION", 2, 2, false);

	VertexBuffer* vbo = new VertexBuffer(positions, sizeof(positions), BufferUsage::STATIC);

#ifdef HT_OPENGL
	Shader* shader = new Shader(layout, "/res/glshader.vert", "/res/glshader.frag");
	glClearColor(0.3f, 0.4f, 0.7f, 1.0f);
#elif defined(HT_DIRECTX)
	Shader* shader = new Shader(layout, "/res/dxshader.vert", "/res/dxshader.frag");

#endif
	shader->Start();
	vbo->Bind(shader->GetStride());

	while (!window.ShouldClose()) {
		window.Clear();

#ifdef HT_DIRECTX
		DIRECTX_CONTEXT->Draw(3, 0);
#else
		glDrawArrays(GL_TRIANGLES, 0, 3);
#endif

		window.Update();
	}

	delete shader;
	delete vbo;

	//system("PAUSE");
	return 0;
}