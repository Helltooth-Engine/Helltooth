#include "Window.hpp"

namespace ht { namespace core {
	using namespace graphics;

	LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		switch (msg) {
		}
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	Window::Window(const std::string& title, int width, int height)
		:m_Title(title), m_Width(width), m_Height(height) {
		printf("Window created %s, width: %i, height %i\n", m_Title.c_str(), m_Width, m_Height);
		WNDCLASSEXA wcex;
		wcex.cbSize			= sizeof(WNDCLASSEX);
		wcex.lpfnWndProc	= WndProc;
		wcex.cbClsExtra		= 0;
		wcex.cbWndExtra		= 0;
		wcex.hInstance		= GetModuleHandleA(nullptr);
		wcex.hIcon			= nullptr;
		wcex.hCursor		= nullptr;
		wcex.hbrBackground	= reinterpret_cast<HBRUSH>(COLOR_ACTIVEBORDER);
		wcex.lpszClassName	= "Helltooth window";
		wcex.lpszMenuName	= 0;
		wcex.hIconSm		= 0;
		wcex.style			= CS_VREDRAW | CS_HREDRAW | CS_OWNDC;

		if (!RegisterClassExA(&wcex)) {
			//proper logging
			printf("Could not register class");
			return;
		}
		m_Hwnd = CreateWindowEx(
			WS_EX_OVERLAPPEDWINDOW,
			L"Helltooth window",
			L"Helltooth window",
			WS_EX_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			m_Width,
			m_Height,
			0,
			0,
			wcex.hInstance,
			0
		);
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
		DestroyWindow(m_Hwnd);
	}

	void Window::Update() {
		MSG msg;
		if (msg.message == WM_DESTROY)
			m_ShouldClose = true;
		if (PeekMessage(&msg, m_Hwnd, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		m_Context->Update();
	}

	void Window::Clear() {
		m_Context->Clear();
	}

	void Window::SetVisible(bool visible) {
		ShowWindow(m_Hwnd, visible ? SW_HIDE : SW_SHOW);
		m_IsVisible = visible;
	}


} }