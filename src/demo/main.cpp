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
		-1.f, -1.f,
		1.f, -1.f,
		0.0f, 1.f
	};


	BufferLayout layout = BufferLayout();
	layout.AddLayout<float>(2, 2, false);

	Shader* shader = new Shader("/res/glshader.vert", "/res/glshader.frag");

	VertexBuffer* vbo = new VertexBuffer(positions, sizeof(positions), BufferUsage::STATIC);
	vbo->Bind();
	VertexArray* vao = new VertexArray(layout);

	vao->Bind();

#ifdef HT_OPENGL
	glClearColor(0.3f, 0.4f, 0.7f, 1.0f);
#endif

	shader->Start();
	while (!window.ShouldClose()) {
		window.Clear();

#ifdef HT_DIRECTX
		Window::GetWindow()->GetDeviceContext()->Draw(6, 0);
#else
		glDrawArrays(GL_TRIANGLES, 0, 3);
#endif

		window.Update();
	}

	delete shader;
	delete vbo;
	delete vao;

	system("PAUSE");
	return 0;
}