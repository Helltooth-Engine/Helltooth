#include "Window.h"

namespace ht { namespace core {
	
	LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		switch (msg) {
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		}
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	Window::Window(const std::wstring& title, int width, int height)
		:title(title), width(width), height(height) {
		printf("Window created %s, width: %i, height %i\n", this->title.c_str(), width, height);
		WNDCLASSEX wcex;
		wcex.cbSize			= sizeof(WNDCLASSEX);
		wcex.style			= CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc	= WndProc;
		wcex.cbClsExtra		= 0;
		wcex.cbWndExtra		= 0;
		wcex.hInstance		= 0;
		wcex.hIcon			= LoadIcon(0, MAKEINTRESOURCE(IDI_APPLICATION));
		wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
		wcex.hbrBackground	= 0;
		wcex.lpszClassName	= L"Helltooth window";
		wcex.lpszMenuName	= 0;
		wcex.hIconSm		= 0;
		wcex.style			= CS_VREDRAW | CS_HREDRAW;

		if (!RegisterClassEx(&wcex)) {
			//proper logging
			printf("Could not register class");
			return;
		}
		hwnd = CreateWindow(L"Helltooth window", this->title.c_str(), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width, height, 0, 0, 0, 0);
		if (!hwnd) {
			DWORD word = GetLastError();
			printf("Could not create window %i!", word);

		}
		ShowWindow(hwnd, SW_SHOW);
		UpdateWindow(hwnd);
		
	}

	Window::~Window() {

	}

} }