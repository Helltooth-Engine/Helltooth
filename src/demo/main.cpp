#include <iostream>
#include <Helltooth.hpp>
#include <gl/GL.h>

#include "Player.hpp"

using namespace std;
using namespace ht;
using namespace core;

int main() {
	Window window(L"Window", 1280, 720);

	Player player = Player();
	EventDispatcher::Add((EventListener*)&player);

	//glClearColor(0.3f, 0.4f, 0.7f, 1.0f);
	while (!window.WindowShouldClose()) {
		window.Clear();
		window.Update();
	}

	system("PAUSE");
	return 0;
}