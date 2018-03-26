#pragma once
#ifdef HT_WINDOWS
#include <Windows.h>
#include <windowsx.h>
#include <tchar.h>
#elif defined(HT_LINUX)
#define XLIB_ILLEGAL_ACCESS
#include <X11/X.h>
#include <X11/Xlib.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>
#endif

#include <stdio.h>
#include <string>
#include <vector>

#include "Internal.hpp"

#include "input/Event.hpp"
#include "input/EventDispatcher.hpp"

#include "graphics/Context.hpp"

#include "utils/Log.hpp"

namespace ht { namespace core {

	class Window {
	private:
		u32 m_Width, m_Height;
		bool m_IsVisible;
		bool m_VSync;
		std::wstring m_Title;
		graphics::Context* m_Context;

#if defined(HT_WINDOWS)
		HWND m_Hwnd;
#elif defined(HT_LINUX)
		_XDisplay* m_Display;
		XID m_Window;
#else
#	error "Others platform is not supported"
#endif
		bool m_ShouldClose = false;

		static Window* s_Window;

	private:
#ifdef HT_WINDOWS
		static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
#endif

	public:
		Window(std::wstring title, u32 width, u32 height);
		~Window();

		void SetVisible(bool visible);
		void Update();
		void Clear();

		inline bool ShouldClose() { return m_ShouldClose; }
		inline graphics::Context* GetContext() { return m_Context; }

		static Window* GetWindow() { return s_Window; }

		void SetTitle(std::wstring title);
#ifdef HT_WINDOWS
		bool IsHWND(HWND other) { return m_Hwnd == other; }
#endif

#ifdef HT_DIRECTX
		inline ID3D11Device* GetDevice() { return m_Context->GetDevice(); }
		inline ID3D11DeviceContext* GetDeviceContext() { return m_Context->GetDeviceContext(); }
#endif
	};

} }
