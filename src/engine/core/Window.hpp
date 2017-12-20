#pragma once
#ifdef HT_WINDOWS
#include <Windows.h>
#include <windowsx.h>
#include <tchar.h>
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
#ifdef HT_WINDOWS
		HWND m_Hwnd;
#else
#	error "Others platform is not supported"
#endif
		bool m_ShouldClose = false;

		static Window* s_Window;

	private:
		static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	public:
		Window(std::wstring title, u32 width, u32 height);
		~Window();

		void SetVisible(bool visible);
		void Update();
		void Clear();

		bool IsHWND(HWND other) { return m_Hwnd == other; }

		inline bool ShouldClose() { return m_ShouldClose; }
		inline graphics::Context* GetContext() { return m_Context; }

		static Window* GetWindow() { return s_Window; }

#ifdef HT_DIRECTX
		inline ID3D11Device* GetDevice() { return m_Context->GetDevice(); }
		inline ID3D11DeviceContext* GetDeviceContext() { return m_Context->GetDeviceContext(); }
#endif
	};

} }
