#include <iostream>
#include <Helltooth.hpp>
#include <random>
#include <time.h>

using namespace ht;
using namespace core;
using namespace maths;
using namespace utils;
using namespace graphics;
using namespace entities;

class Game : public Application {
private:
	Camera* camera;
	std::vector<Entity> entities;
	std::vector<TransformComponent> transforms;
	ModelComponent* model;
	UniformBuffer* buffer;
	Texture* texture;
	Matrix4 proj;
	Renderer* renderer;

public:
	// In here you should initialize stuff that's not depended to the rendering context
	Game() 
		: Application("Window", 1280, 720) {
		srand(time(NULL));
		VFS::Mount("res", "res/shaders/");
		VFS::Mount("res", "res/textures/");
		VFS::Mount("res", "res/models/");

		camera = new FPSCamera(0, 0, -100);
	}

	~Game() {
		delete camera, renderer, buffer, model, texture;
	}

	void Init() {
		proj = Matrix4::CreatePerspective(70, 0.01f, 1000.0f, 2.34f);
		renderer = new Renderer(camera, proj);
		model = Asset::LoadModel("/res/cube.htmodel");
		transforms.resize(500);
		for (int i = 0; i < 500; i++) {
			entities.emplace_back();
			entities[i].AddComponent(model);
			transforms[i] = TransformComponent(Vector3((f32)rand() / (f32)RAND_MAX * 200.f - 100.0f, (f32)rand() / (f32)RAND_MAX * 200.f - 100.0f, (f32)rand() / (f32)RAND_MAX * 200.f - 100.0f));
			//transforms[i].Scale(1, 1, 1);
			entities[i].AddComponent(&transforms[i]);
		}

#ifdef HT_OPENGL
		glClearColor(0.3f, 0.4f, 0.7f, 1.0f);
		glEnable(GL_DEPTH_TEST);
#endif
		texture = Asset::LoadTexture("/res/cube.httexture");

		texture->Bind(0);
	}

	void Render() {
		for(u32 i=0; i < entities.size(); i++)
			renderer->Submit(entities[i]);
		renderer->Render();
		renderer->End();
	}

	void Update(float delta) {
		camera->Update(delta);
		for (TransformComponent& transform : transforms) {
			transform.Rotate(0, 50.f * delta, 0);
			transform.Update(delta);
		}
	}

	void Tick() {

	}

};

int main() {
	Game game;
	game.Start();

	return 0;
}
