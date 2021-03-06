﻿/*
 * Copyright (c) 2020 Rareș-Nicolaie Ciorbă
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#ifdef HT_WINDOWS
#include "core/Window.hpp"

namespace ht { namespace core {
	using namespace graphics;

	Window* Window::s_Window = nullptr;

	Window::Window(std::string title, u32 width, u32 height)
		:m_Title(title), m_Width(width), m_Height(height) {

#if defined(HT_OPENGL)
		m_Title.append(" - OpenGL");
#elif defined (HT_DIRECTX)
		m_Title.append(" - DirectX");
#endif // HT_OPENGL

		WNDCLASSEXA wcex = {};

		wcex.cbSize         = sizeof(WNDCLASSEX);
		wcex.lpfnWndProc    = WndProc;
		wcex.cbClsExtra     = 0;
		wcex.cbWndExtra     = 0;
		wcex.hInstance      = GetModuleHandleA(nullptr);
		wcex.hIcon          = nullptr;
		wcex.hCursor        = LoadCursorA(NULL, MAKEINTRESOURCEA(32512));
		wcex.hbrBackground  = 0;
		wcex.lpszClassName  = "Helltooth window";
		wcex.lpszMenuName   = 0;
		wcex.hIconSm        = 0;
		wcex.style          = CS_VREDRAW | CS_HREDRAW | CS_OWNDC;

		if (!RegisterClassExA(&wcex)) {
			DWORD word = GetLastError();
			HT_FATAL("[Window] Could not register window class, %d!", word);
			return;
		}

		m_Hwnd = CreateWindowA("Helltooth window", m_Title.c_str(), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, m_Width, m_Height, 0, 0, wcex.hInstance, 0);

		if (!m_Hwnd) {
			DWORD word = GetLastError();
			HT_FATAL("[Window] Could not create window, %d!", word);
			return;

		}

		SetVisible(true);
		SetFocus(m_Hwnd);
		UpdateWindow(m_Hwnd);
		HT_ASSERT(s_Window == nullptr, "Multiple windows not supported!");
		s_Window = this;
		m_Context = new Context(m_Hwnd);
	}

	Window::~Window() {
		DestroyWindow(m_Hwnd);
		m_Hwnd = nullptr; 
		delete m_Context;
		s_Window = nullptr;
	}

	void Window::Update() {
		MSG msg;
		if (PeekMessageA(&msg, m_Hwnd, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessageA(&msg);
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

	void Window::SetTitle(std::string title) {
#if defined(HT_OPENGL)
		title.append(" - OpenGL");
#elif defined(HT_DIRECTX)
		title.append(" - DirectX");
#endif // HT_OPENGL
		SetWindowTextA(m_Hwnd, title.c_str());
	}

	LRESULT Window::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		Window* window = Window::GetWindow();

		Event *e = new Event();
		bool inputEvent = false;
		switch (msg) {
		case WM_CLOSE:
			window->m_ShouldClose = true;
			break;
		case WM_KEYDOWN:
			e->eventType                 = EventType::KEYBOARD;
			e->key.key                   = static_cast<u16>(wParam);
			e->key.modifiers             = static_cast<u16>(Modifier::NONE);
			e->key.state                 = State::PRESSED;
			inputEvent                   = true;
			break;
		case WM_KEYUP:
			e->eventType                 = EventType::KEYBOARD;
			e->key.key                   = static_cast<u16>(wParam);
			e->key.modifiers             = static_cast<u16>(Modifier::NONE);
			e->key.state                 = State::RELEASED;
			inputEvent                   = true;
			break;
		case WM_LBUTTONDOWN:
			e->eventType                 = EventType::MOUSE;
			e->mouse.mouseButton         = HT_MOUSE_LBUTTON;
			e->mouse.mouseButtonState    = State::PRESSED;
			e->mouse.x                   = static_cast<f32>(GET_X_LPARAM(lParam));
			e->mouse.y                   = static_cast<f32>(GET_Y_LPARAM(lParam));
			inputEvent                   = true;
			break;
		case WM_LBUTTONUP:
			e->eventType                 = EventType::MOUSE;
			e->mouse.mouseButton         = HT_MOUSE_LBUTTON;
			e->mouse.mouseButtonState    = State::RELEASED;
			e->mouse.x                   = static_cast<f32>(GET_X_LPARAM(lParam));
			e->mouse.y                   = static_cast<f32>(GET_Y_LPARAM(lParam));
			inputEvent                   = true;
			break;
		case WM_RBUTTONDOWN:
			e->eventType                 = EventType::MOUSE;
			e->mouse.mouseButton         = HT_MOUSE_RBUTTON;
			e->mouse.mouseButtonState    = State::PRESSED;
			e->mouse.x                   = static_cast<f32>(GET_X_LPARAM(lParam));
			e->mouse.y                   = static_cast<f32>(GET_Y_LPARAM(lParam));
			inputEvent                   = true;
			break;
		case WM_RBUTTONUP:
			e->eventType                 = EventType::MOUSE;
			e->mouse.mouseButton         = HT_MOUSE_RBUTTON;
			e->mouse.mouseButtonState    = State::RELEASED;
			e->mouse.x                   = static_cast<f32>(GET_X_LPARAM(lParam));
			e->mouse.y                   = static_cast<f32>(GET_Y_LPARAM(lParam));
			inputEvent                   = true;
			break;
		case WM_MBUTTONDOWN:
			e->eventType                 = EventType::MOUSE;
			e->mouse.mouseButton         = HT_MOUSE_BUTTON3;
			e->mouse.mouseButtonState    = State::PRESSED;
			e->mouse.x                   = static_cast<f32>(GET_X_LPARAM(lParam));
			e->mouse.y                   = static_cast<f32>(GET_Y_LPARAM(lParam));
			inputEvent                   = true;
			break;
		case WM_MBUTTONUP:
			e->eventType                 = EventType::MOUSE;
			e->mouse.mouseButton         = HT_MOUSE_BUTTON3;
			e->mouse.mouseButtonState    = State::RELEASED;
			e->mouse.x                   = static_cast<f32>(GET_X_LPARAM(lParam));
			e->mouse.y                   = static_cast<f32>(GET_Y_LPARAM(lParam));
			inputEvent                   = true;
			break;
		case WM_MOUSEMOVE:
			e->eventType                 = EventType::MOUSE;
			e->mouse.mouseButton         = -1;
			e->mouse.mouseButtonState    = State::NONE;
			e->mouse.x                   = static_cast<f32>(GET_X_LPARAM(lParam));
			e->mouse.y                   = static_cast<f32>(GET_Y_LPARAM(lParam));
			inputEvent                   = true;
			break;
		case WM_SIZE:
			if(window)
				window->Resize(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			break;
		}
		if(inputEvent)
			EventDispatcher::Dispatch(e);
		delete e;
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}

} }

#endif