#include "Window.h"

namespace ht { namespace core {
	
	Window::Window(const std::string& title, int width, int height) {
		printf("Window created %s, width: %i, height %i", title.c_str(), width, height);
	}


} }