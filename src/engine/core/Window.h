#include <Windows.h>

#include <stdio.h>
#include <string>

namespace ht { namespace core {

	class Window {
	private:
		int width, height;
		bool isVisible;
		unsigned int vSync;
		std::string title;
		HWND hwnd;

	public:
		Window(const std::string& title, int width, int height);
		~Window() {} //crying internally


	};

} }
