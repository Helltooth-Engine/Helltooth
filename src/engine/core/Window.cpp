#include "Window.hpp"

namespace ht { namespace core {
	using namespace graphics;

	LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		switch (msg) {
		case WM_DESTROY:
			m_ShouldClose = true;
			break;
		}
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	Window::Window(const std::wstring& title, int width, int height)
		:m_Title(title), m_Width(width), m_Height(height) {
		printf("Window created %s, width: %i, height %i\n", m_Title.c_str(), m_Width, m_Height);
		WNDCLASSEX wcex;
		wcex.cbSize			= sizeof(WNDCLASSEX);
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
		m_Hwnd = CreateWindow(L"Helltooth window", m_Title.c_str(), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, m_Width, m_Height, 0, 0, 0, 0);
		if (!m_Hwnd) {
			DWORD word = GetLastError();
			printf("Could not create window %i!", word);

		}
		ShowWindow(m_Hwnd, SW_SHOW);
		m_IsVisible = true;
		UpdateWindow(m_Hwnd);
		m_Context = new Context(m_Hwnd);
	}

	Window::~Window() {
		delete m_Context;
	}

	void Window::SwapBuffers() {
		MSG msg;
		if (PeekMessage(&msg, m_Hwnd, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	void Window::SetVisible(bool visible) {
		ShowWindow(m_Hwnd, visible ? SW_HIDE : SW_SHOW);
		m_IsVisible = visible;
	}


} }