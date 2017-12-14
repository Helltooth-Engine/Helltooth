#include <iostream>
#include <Helltooth.hpp>

using namespace std;
using namespace ht;
using namespace core;


int main() {
	Window window(L"Window", 1280, 720);

	while (true) {
		window.SwapBuffers();
	}

	system("PAUSE");
	return 0;
}