#include <Windows.h>
#include <tchar.h>

#include <stdio.h>
#include <string>

namespace ht { namespace core {

	class Window {
	private:
		int width, height;
		bool isVisible;
		unsigned int vSync;
		std::wstring title;
		HWND hwnd;

	public:
		Window(const std::wstring& title, int width, int height);
		~Window();


		void SwapBuffers() {
			MSG msg;
			if (PeekMessage(&msg, hwnd, 0, 0, PM_REMOVE)) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}

	};

} }
