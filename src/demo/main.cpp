#include <iostream>
#include <Helltooth.hpp>
#include <gl/GL.h>

#include <graphics/shaders/Shader.hpp>

#include "Player.hpp"

using namespace std;
using namespace ht;
using namespace core;
using namespace maths;
using namespace utils;

int main() {
	Window window(L"Window", 1280, 720);

	VFS::Mount("res", "res/shaders/");
	VFS::Mount("res", "res/textures/");

	float positions[] = {
		-0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, -1.0f, 0.0f, 1.0f,
		 0.5f,  0.5f, -1.0f, 1.0f, 1.0f,
		 0.5f, -0.5f, -1.0f, 1.0f, 0.0f
	};

	u16 indices[] = {
		0, 2, 1,
		0, 3, 2
	};

	BufferLayout* layout = new BufferLayout();
	layout->AddLayout<float>("POSITION", 3, 3, false);
	layout->AddLayout<float>("UVS", 2, 2, false);

#ifdef HT_OPENGL
	Shader* shader = new Shader(layout, "/res/glshader.vert", "/res/glshader.frag");
	s32 ids[] = { 0, 1 };
	shader->SetSamplers(ids, 2);

	glClearColor(0.3f, 0.4f, 0.7f, 1.0f);
#elif defined(HT_DIRECTX)
	Shader* shader = new Shader(layout, "/res/dxshader.vert", "/res/dxshader.frag");
#endif
	VertexBuffer* vbo = new VertexBuffer(positions, sizeof(positions), BufferUsage::STATIC);
	
	IndexBuffer* ibo = new IndexBuffer(indices, 6, BufferUsage::STATIC);

	UniformBufferLayout ulayout(ShaderType::VERTEX);
	ulayout.AddUniform<Matrix4>();
	ulayout.AddUniform<Matrix4>();

	Matrix4 proj = Matrix4::CreatePerspective(70, 0.01f, 1000.0f, 1.77f);
	Matrix4 mdl = Matrix4(1.0f);

	UniformBuffer* buffer = new UniformBuffer(ulayout);
	buffer->Set(0, &proj[0]);
	buffer->Set(1, &mdl[0]);
	
	Texture* texture = Asset::LoadTexture("/res/final_logo.httexture");

	texture->Bind();
	glActiveTexture(GL_TEXTURE0);
	int rot = 0;
	while (!window.ShouldClose()) {
		window.Clear();
		vbo->Bind(shader->GetStride());
		shader->Start();
		mdl.Rotate(Vector3(0, 0, 0.05f));
		buffer->Set(1, &mdl[0]);
		ibo->Bind();
		buffer->Bind();
#ifdef HT_DIRECTX
		HT_DXCONTEXT->DrawIndexed(ibo->GetCount(), 0, 0);
#else
		glDrawElements(GL_TRIANGLES, ibo->GetCount(), ibo->GetFormat(), 0);
#endif

		window.Update();
	}

	delete shader;
	delete vbo;

	//system("PAUSE");
	return 0;
}