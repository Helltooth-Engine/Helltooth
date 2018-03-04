#include <iostream>
#include <Helltooth.hpp>
#include <gl/GL.h>

#include <graphics/shaders/Shader.hpp>

using namespace std;
using namespace ht;
using namespace core;
using namespace maths;
using namespace utils;
using namespace graphics;

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
		1, 2, 0,
		2, 3, 0
	};

	Camera* camera = new FPSCamera(0, 0, 0);

	BufferLayout* layout = new BufferLayout();
	layout->AddLayout<float>("POSITION", 3, 3, false);
	layout->AddLayout<float>("UVS", 2, 2, false);

	Entity* entity = new Entity();
	Shader* shader = new Shader(layout, "/res/shader.vert", "/res/shader.frag", ShaderLocationType::FROM_PATH | ShaderLocationType::FROM_HTSL);

#ifdef HT_OPENGL
	s32 ids[] = { 0, 1 };
	shader->SetSamplers(ids, 2);

	glClearColor(0.3f, 0.4f, 0.7f, 1.0f);
#endif
	VertexBuffer* vbo = new VertexBuffer(positions, sizeof(positions), BufferUsage::STATIC);
	
	IndexBuffer* ibo = new IndexBuffer(indices, 6, BufferUsage::STATIC);

	UniformBufferLayout ulayout(ShaderType::VERTEX);
	ulayout.AddUniform<Matrix4>();
	ulayout.AddUniform<Matrix4>();
	ulayout.AddUniform<Matrix4>();

	Matrix4 proj = Matrix4::CreatePerspective(70, 0.01f, 1000.0f, 1.77f);
	Matrix4 viewMatrix = Matrix4(1.0f);
	UniformBuffer* buffer = new UniformBuffer(ulayout);
	buffer->Set(0, &proj[0]);
	buffer->Set(1, &viewMatrix[0]);
	buffer->Set(2, &entity->GetModelMatrix()[0]);

	Texture* texture = Asset::LoadTexture("/res/final_logo.httexture");

	texture->Bind(0);
	int rot = 0;
	Timer timer;

	vbo->Bind(shader->GetStride()); 
	shader->Start();
	ibo->Bind();
	buffer->Bind();
	float delta = 0.0f;
	while (!window.ShouldClose()) {
		window.Clear();
		camera->Update(delta);
		entity->Rotate(50.f * delta, 50.f * delta, 50.f * delta);

		entity->Update(delta);
		
		viewMatrix = camera->GetViewMatrix();

		buffer->Set(1, &viewMatrix[0]);
		buffer->Set(2, &entity->GetModelMatrix()[0]);
		buffer->Bind();

#ifdef HT_DIRECTX
		HT_DXCONTEXT->DrawIndexed(ibo->GetCount(), 0, 0);
#else
		glDrawElements(GL_TRIANGLES, ibo->GetCount(), ibo->GetFormat(), 0);
#endif

		window.Update();
		delta = timer.GetDelta();
		float frames = 1.0f / delta;
		window.SetTitle(L"Window | frames: " + std::to_wstring(frames));
	}

	delete shader, vbo, buffer, camera, layout, entity, texture, ibo;

	//system("PAUSE");
	return 0;
}