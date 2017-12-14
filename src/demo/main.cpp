#include <iostream>
#include <Helltooth.hpp>

using namespace std;
using namespace ht;
using namespace core;


int main() {
	Window window("Window", 1280, 720);

	while (!window.WindowShouldClose()) {
		window.Clear();
		glClearColor(0.3f, 0.4f, 0.7f, 1.0f);
		window.Update();
	}

	system("PAUSE");
	return 0;
}