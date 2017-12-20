#include <iostream>
#include <Helltooth.hpp>
#include <gl/GL.h>

#include "Player.hpp"

using namespace std;
using namespace ht;
using namespace core;

int main() {
	Window window(L"Window", 1280, 720);

	float positions[] = {
		-0.5f, -0.5f,
		0.5f, -0.5f,
		0.0f, 0.5f
	};

	BufferLayout layout;
	layout.AddLayout<float>(2, 2, false);

	VertexBuffer* buffer = new VertexBuffer(positions, 3 * 2 * sizeof(float), layout, BufferUsage::STATIC);

	Player player = Player();
	EventDispatcher::Add((EventListener*)&player);
#ifdef HT_OPENGL
	glClearColor(0.3f, 0.4f, 0.7f, 1.0f);
#endif
	while (!window.ShouldClose()) {
		window.Clear();
		buffer->Bind();
#ifdef HT_DIRECTX
		Window::GetWindow()->GetDeviceContext()->Draw(6, 0);
#else
		glDrawArrays(GL_TRIANGLES, 0, 6);
#endif
		window.Update();
	}

	system("PAUSE");
	return 0;
}