#include <iostream>
#include <Helltooth.hpp>

using namespace ht;
using namespace core;
using namespace maths;
using namespace utils;
using namespace graphics;
using namespace entities;

class Game : public Application {
private:
	Camera* camera;
	BufferLayout* layout;
	Entity entity;
	TransformComponent transform;
	ModelComponent* model;
	Shader* shader;
	UniformBuffer* buffer;
	Texture* texture;
	Matrix4 proj, viewMatrix;

public:
	// In here you should initialize stuff that's not depended to the rendering context
	Game() 
		: Application("Window", 1280, 720) {
		VFS::Mount("res", "res/shaders/");
		VFS::Mount("res", "res/textures/");
		VFS::Mount("res", "res/models/");

		camera = new FPSCamera(0, 0, -5);
		entity.AddComponent(&transform);
	}

	~Game() {
		delete camera, layout, entity, shader, buffer, model, texture;
	}

	void Init() {
		layout = new BufferLayout();
		layout->AddLayout<float>("POSITION", 3, false);
		layout->AddLayout<float>("UV", 2, false);
		layout->AddLayout<float>("NORMALS", 3, false);

		shader = new Shader(layout, "/res/shader.vert", "/res/shader.frag", ShaderLocationType::FROM_PATH | ShaderLocationType::FROM_HTSL);
		model = Asset::LoadModel("/res/cube.htmodel");
		entity.AddComponent(model);

#ifdef HT_OPENGL
		s32 ids[] = { 0, 1 };
		shader->SetSamplers(ids, 2);

		glClearColor(0.3f, 0.4f, 0.7f, 1.0f);
#endif

		UniformBufferLayout ulayout(ShaderType::VERTEX);
		ulayout.AddUniform<Matrix4>();
		ulayout.AddUniform<Matrix4>();
		ulayout.AddUniform<Matrix4>();

		proj = Matrix4::CreatePerspective(70, 0.01f, 1000.0f, 1.77f);
		viewMatrix = Matrix4(1.0f);

		buffer = new UniformBuffer(ulayout);
		buffer->Set(0, &proj[0]);
		buffer->Set(1, &viewMatrix[0]);
		buffer->Set(2, &transform.GetModelMatrix()[0]);

		texture = Asset::LoadTexture("/res/cube.httexture");

		texture->Bind(0);
#if defined(HT_OPENGL)
		glEnable(GL_DEPTH_TEST);
#endif
	}

	void Render() {
		shader->Start();
		model->Bind(shader->GetStride());
		shader->BindLayout();
		model->Render();
	}

	void Update(float delta) {
		camera->Update(delta);
		transform.Rotate(50.f * delta, 50.f * delta, 50.f * delta);
		transform.Update(delta);
		viewMatrix = camera->GetViewMatrix();

		buffer->Set(1, &viewMatrix[0]);
		buffer->Set(2, &transform.GetModelMatrix()[0]);
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
