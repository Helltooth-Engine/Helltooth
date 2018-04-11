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
	Entity entity;
	TransformComponent transform;
	ModelComponent* model;
	UniformBuffer* buffer;
	Texture* texture;
	Matrix4 proj;
	Renderer* renderer;

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
		delete camera, renderer, entity, buffer, model, texture;
	}

	void Init() {
		proj = Matrix4::CreatePerspective(70, 0.01f, 1000.0f, 1.77f);
		renderer = new Renderer(camera, proj);
		model = Asset::LoadModel("/res/cube.htmodel");
		entity.AddComponent(model);

#ifdef HT_OPENGL
		glClearColor(0.3f, 0.4f, 0.7f, 1.0f);
		glEnable(GL_DEPTH_TEST);
#endif
		texture = Asset::LoadTexture("/res/cube.httexture");

		texture->Bind(0);
	}

	void Render() {
		renderer->Submit(entity);
		renderer->Render();
		renderer->End();
	}

	void Update(float delta) {
		camera->Update(delta);
		transform.Rotate(50.f * delta, 50.f * delta, 50.f * delta);
		transform.Update(delta);
	}

	void Tick() {

	}

};

int main() {
	Game game;
	game.Start();

	return 0;
}
