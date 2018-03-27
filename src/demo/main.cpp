#include <iostream>
#include <Helltooth.hpp>

#include <graphics/shaders/Shader.hpp>

using namespace ht;
using namespace core;
using namespace maths;
using namespace utils;
using namespace graphics;

class Game : public Application {
private:
	Camera* camera;
	BufferLayout* layout;
	Entity* entity;
	Shader* shader;
	VertexBuffer* vbo;
	IndexBuffer* ibo;
	UniformBuffer* buffer;
	Texture* texture;
	Matrix4 proj, viewMatrix;

public:
	// In here you should initialize stuff that's not depended to the rendering context
	Game() 
		: Application(L"Window", 1280, 720) {
		VFS::Mount("res", "res/shaders/");
		VFS::Mount("res", "res/textures/");

		camera = new FPSCamera(0, 0, 0);
		entity = new Entity();
	}

	~Game() {
		delete camera, layout, entity, shader, vbo, ibo, buffer, texture;
	}

	void Init() {
		float data[] = {
			-0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
			-0.5f,  0.5f, -1.0f, 0.0f, 1.0f,
			0.5f,  0.5f, -1.0f, 1.0f, 1.0f,
			0.5f, -0.5f, -1.0f, 1.0f, 0.0f
		};

		u16 indices[] = {
			1, 2, 0,
			2, 3, 0
		};

		layout = new BufferLayout();
		layout->AddLayout<float>("UV", 2, 2, false);
		layout->AddLayout<float>("POSITION", 3, 3, false);


		shader = new Shader(layout, "/res/shader.vert", "/res/shader.frag", ShaderLocationType::FROM_PATH | ShaderLocationType::FROM_HTSL);
		vbo = new VertexBuffer(data, sizeof(data), BufferUsage::STATIC);

#ifdef HT_OPENGL
		s32 ids[] = { 0, 1 };
		shader->SetSamplers(ids, 2);

		glClearColor(0.3f, 0.4f, 0.7f, 1.0f);
#endif

		ibo = new IndexBuffer(indices, 6, BufferUsage::STATIC);

		UniformBufferLayout ulayout(ShaderType::VERTEX);
		ulayout.AddUniform<Matrix4>();
		ulayout.AddUniform<Matrix4>();
		ulayout.AddUniform<Matrix4>();

		proj = Matrix4::CreatePerspective(70, 0.01f, 1000.0f, 1.77f);
		viewMatrix = Matrix4(1.0f);

		buffer = new UniformBuffer(ulayout);
		buffer->Set(0, &proj[0]);
		buffer->Set(1, &viewMatrix[0]);
		buffer->Set(2, &entity->GetModelMatrix()[0]);

		texture = Asset::LoadTexture("/res/final_logo.httexture");

		texture->Bind(0);

		vbo->Bind(shader->GetStride());
		shader->Start();
		ibo->Bind();
		buffer->Bind();
	}

	void Render() {
#ifdef HT_DIRECTX
		HT_DXCONTEXT->DrawIndexed(ibo->GetCount(), 0, 0);
#else
		glDrawElements(GL_TRIANGLES, ibo->GetCount(), ibo->GetFormat(), 0);
#endif
	}

	void Update(float delta) {
		camera->Update(delta);
		entity->Rotate(50.f * delta, 50.f * delta, 50.f * delta);
		entity->Update(delta);
		viewMatrix = camera->GetViewMatrix();

		buffer->Set(1, &viewMatrix[0]);
		buffer->Set(2, &entity->GetModelMatrix()[0]);
		buffer->Bind();
	}

	void Tick() {

	}

};

int main() {
	Game game;
	game.Start();

	return 0;
}
