/*
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

#pragma once
#if defined(HT_WINDOWS)
#include <Windows.h>
#include <windowsx.h>
#include <tchar.h>
#elif defined(HT_LINUX)
//#define XLIB_ILLEGAL_ACCESS
#include <X11/X.h>
#include <X11/Xlib.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>
#endif // HT_WINDOWS

#include <stdio.h>
#include <string>
#include <vector>

#include "core/Internal.hpp"

#include "core/input/Event.hpp"
#include "core/input/EventDispatcher.hpp"

#include "graphics/Context.hpp"

#include "utils/Log.hpp"

namespace ht { namespace core {

	class Window {
	private:
		u32 m_Width, m_Height;
		bool m_IsVisible;
		bool m_VSync;
		std::string m_Title;
		graphics::Context* m_Context;

#if defined(HT_WINDOWS)
		HWND m_Hwnd;
#elif defined(HT_LINUX)
		_XDisplay* 		m_Display = nullptr;
		XID 			m_Window;
		Atom            m_WindowDestroyAtom;
		
#endif // HT_WINDOWS
		bool m_ShouldClose = false;

		static Window* s_Window;

	
	public:
		Window(std::string title, u32 width, u32 height);
		~Window();

		static Window* GetWindow() { return s_Window; }

		void SetVisible(bool visible);
		void Update();
		void Clear();


		void SetTitle(std::string title);
#if defined(HT_WINDOWS)
		inline bool IsHWND(HWND other) { return m_Hwnd == other; }
#endif // HT_WINDOWS

		inline bool ShouldClose() { return m_ShouldClose; }
		inline graphics::Context* GetContext() { return m_Context; }
		inline void Resize(u32 width, u32 height) { m_Width = width; m_Height = height; m_Context->Resize(width, height); }

#if defined(HT_DIRECTX)
		inline ID3D11Device* GetDevice() { return m_Context->GetDevice(); }
		inline ID3D11DeviceContext* GetDeviceContext() { return m_Context->GetDeviceContext(); }
#endif // HT_DIRECTX

	private:
#ifdef HT_WINDOWS
		static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
#elif defined(HT_LINUX)
		static void HandleXEvent(const XEvent& event);
#endif // HT_WINDOWS

	};

} }
