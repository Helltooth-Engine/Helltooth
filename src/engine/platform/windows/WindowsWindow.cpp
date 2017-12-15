#ifdef HT_WINDOWS
#include "core/Window.hpp"

namespace ht { namespace core {
	using namespace graphics;

	LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		switch (msg) {
		}
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	Window::Window(std::wstring title, int width, int height)
		:m_Title(title), m_Width(width), m_Height(height) {

		WNDCLASSEX wcex;
		wcex.cbSize			= sizeof(WNDCLASSEX);
		wcex.lpfnWndProc	= WndProc;
		wcex.cbClsExtra		= 0;
		wcex.cbWndExtra		= 0;
		wcex.hInstance		= GetModuleHandleA(nullptr);
		wcex.hIcon			= nullptr;
		wcex.hCursor		= nullptr;
		wcex.hbrBackground	= 0;
		wcex.lpszClassName	= L"Helltooth window";
		wcex.lpszMenuName	= 0;
		wcex.hIconSm		= 0;
		wcex.style			= CS_VREDRAW | CS_HREDRAW | CS_OWNDC;

		if (!RegisterClassEx(&wcex)) {
			DWORD word = GetLastError();
			HT_FATAL("[Window] Could not register window class, %d!", word);
			return;
		}
		m_Hwnd = CreateWindow(L"Helltooth window", m_Title.c_str(),
			WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, m_Width, m_Height, 0, 0, wcex.hInstance, 0);


		if (!m_Hwnd) {
			DWORD word = GetLastError();
			HT_FATAL("[Window] Could not create window, %d!", word);
			return;

		}
		SetVisible(true);
		SetFocus(m_Hwnd);
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
		ShowWindow(m_Hwnd, visible ? SW_SHOW : SW_HIDE);
		m_IsVisible = visible;
	}

} }
#endif