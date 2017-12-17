#ifdef HT_WINDOWS
#include "core/Window.hpp"

namespace ht { namespace core {
	using namespace graphics;

	Window* Window::s_Window = nullptr;

	LRESULT Window::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		Window* window = Window::GetWindow();
		Event *e = new Event();
		bool inputEvent = false;
		switch (msg) {
		case WM_CLOSE:
			window->m_ShouldClose = true;
			break;
		case WM_KEYDOWN:
			e->m_EventType = EventType::KEYBOARD;
			e->m_Key.key = wParam;
			e->m_Key.modifiers = (unsigned short)Modifier::NONE;
			e->m_Key.state = State::PRESSED;
			inputEvent = true;
			break;
		case WM_KEYUP:
			e->m_EventType = EventType::KEYBOARD;
			e->m_Key.key = wParam;
			e->m_Key.modifiers = (unsigned short)Modifier::NONE;
			e->m_Key.state = State::RELEASED;
			inputEvent = true;
			break;
		case WM_LBUTTONDOWN:
			e->m_EventType = EventType::MOUSE;
			e->m_Mouse.mouseButton = HT_MOUSE_LBUTTON;
			e->m_Mouse.mouseButtonState = State::PRESSED;
			e->m_Mouse.x = GET_X_LPARAM(lParam);
			e->m_Mouse.y = GET_Y_LPARAM(lParam);
			inputEvent = true;
			break;
		case WM_LBUTTONUP:
			e->m_EventType = EventType::MOUSE;
			e->m_Mouse.mouseButton = HT_MOUSE_LBUTTON;
			e->m_Mouse.mouseButtonState = State::RELEASED;
			e->m_Mouse.x = GET_X_LPARAM(lParam);
			e->m_Mouse.y = GET_Y_LPARAM(lParam);
			inputEvent = true;
			break;
		case WM_RBUTTONDOWN:
			e->m_EventType = EventType::MOUSE;
			e->m_Mouse.mouseButton = HT_MOUSE_RBUTTON;
			e->m_Mouse.mouseButtonState = State::PRESSED;
			e->m_Mouse.x = GET_X_LPARAM(lParam);
			e->m_Mouse.y = GET_Y_LPARAM(lParam);
			inputEvent = true;
			break;
		case WM_RBUTTONUP:
			e->m_EventType = EventType::MOUSE;
			e->m_Mouse.mouseButton = HT_MOUSE_RBUTTON;
			e->m_Mouse.mouseButtonState = State::RELEASED;
			e->m_Mouse.x = GET_X_LPARAM(lParam);
			e->m_Mouse.y = GET_Y_LPARAM(lParam);
			inputEvent = true;
			break;
		case WM_MBUTTONDOWN:
			e->m_EventType = EventType::MOUSE;
			e->m_Mouse.mouseButton = HT_MOUSE_BUTTON3;
			e->m_Mouse.mouseButtonState = State::PRESSED;
			e->m_Mouse.x = GET_X_LPARAM(lParam);
			e->m_Mouse.y = GET_Y_LPARAM(lParam);
			inputEvent = true;
			break;
		case WM_MBUTTONUP:
			e->m_EventType = EventType::MOUSE;
			e->m_Mouse.mouseButton = HT_MOUSE_BUTTON3;
			e->m_Mouse.mouseButtonState = State::RELEASED;
			e->m_Mouse.x = GET_X_LPARAM(lParam);
			e->m_Mouse.y = GET_Y_LPARAM(lParam);
			inputEvent = true;
			break;
		case WM_MOUSEMOVE:
			e->m_EventType = EventType::MOUSE;
			e->m_Mouse.mouseButton = -1;
			e->m_Mouse.mouseButtonState = State::NONE;
			e->m_Mouse.x = GET_X_LPARAM(lParam);
			e->m_Mouse.y = GET_Y_LPARAM(lParam);
			inputEvent = true;
			break;
		}
		if(inputEvent)
			EventDispatcher::Dispatch(e);
		delete e;
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
		HT_ASSERT(s_Window != nullptr, "Multiple windows not supported!");
		m_Context = new Context(m_Hwnd);
	}

	Window::~Window() {
		s_Window = nullptr;
		delete m_Context;
		DestroyWindow(m_Hwnd);
	}

	void Window::Update() {
		MSG msg;
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