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

#ifdef HT_OPENGL
#include "graphics/Context.hpp"

namespace ht { namespace graphics {

#if defined(HT_WINDOWS)
	Context::Context(HWND& hwnd)
		:m_Hwnd(hwnd) {

		PIXELFORMATDESCRIPTOR pfd = {};

		pfd.nSize       = sizeof(PIXELFORMATDESCRIPTOR);
		pfd.nVersion    = 1;
		pfd.dwFlags     = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		pfd.iPixelType  = PFD_TYPE_RGBA;
		pfd.cColorBits  = 32;
		pfd.cDepthBits  = 32;
		pfd.iLayerType  = PFD_MAIN_PLANE;

		m_DeviceContext = GetDC(hwnd);
		int pixelFormat = ChoosePixelFormat(m_DeviceContext, &pfd);
		if (pixelFormat == 0) {
			DWORD err = GetLastError();
			HT_FATAL("[GLContext] Could not choose pixel format, %d!", err);
			return;
		}

		SetPixelFormat(m_DeviceContext, pixelFormat, &pfd);
		HGLRC fakeContext = wglCreateContext(m_DeviceContext);
		if (!wglMakeCurrent(m_DeviceContext, fakeContext)) {
			DWORD err = GetLastError();
			HT_FATAL("[GLContext] Could not create context, %d !", err);
			return;
		}

		wglInit();

		int attribs[] = {
			WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
#if defined(HT_DEBUG)
			WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_DEBUG_BIT_ARB,
#else
			WGL_CONTEXT_FLAGS_ARB,
#endif // HT_DEBUG
			0, 0
		};

		m_Context = wglCreateContextAttribsARB(m_DeviceContext, NULL, attribs);
		if (!m_Context) {
			DWORD err = GetLastError();
			HT_FATAL("[GLContext] Could not create context, %d !", err);
			return;
		}

		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(fakeContext);

		if (!wglMakeCurrent(m_DeviceContext, m_Context)) {
			DWORD err = GetLastError();
			HT_FATAL("[GLContext] Could not make context current, %d !", err);
			return;
		}
		
		HT_WARN("GL version: %s",                   reinterpret_cast<const char*>(glGetString(GL_VERSION)));
		HT_WARN("GL vendor: %s",                    reinterpret_cast<const char*>(glGetString(GL_VENDOR)));
		HT_WARN("GL renderer: %s",                  reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
		HT_WARN("GL shading language version: %s",  reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION)));

		wglSwapIntervalEXT(0);

		if (!GLInit()) {
			DWORD err = GetLastError(); 
			HT_FATAL("[GLContext] Could not initialize GL, %d!", err);
		}
	}

	Context::~Context() {
		wglMakeCurrent(m_DeviceContext, NULL);
		wglDeleteContext(m_Context);
		ReleaseDC(m_Hwnd, m_DeviceContext);
	}

	void Context::Update() {
		SwapBuffers(m_DeviceContext);
	}

#elif defined(HT_LINUX)

	Context::Context(_XDisplay* display, XID& window, GLXFBConfig fbConfig)
		: m_Display(display), m_Window(window) {
		if (!lglInit()) {
			HT_FATAL("%s", "[GLContext] Could not initialize LGL");
			return;
		}
		
		int contextAttribs[] = {
			GLX_CONTEXT_MAJOR_VERSION_ARB, 	4,
			GLX_CONTEXT_MINOR_VERSION_ARB, 	0,
			GLX_CONTEXT_FLAGS_ARB,			GLX_CONTEXT_CORE_PROFILE_BIT_ARB,
			None
		};

		m_Context = glXCreateContextAttribsARB(m_Display, fbConfig, 0, True, contextAttribs);

		//m_Context = glXCreateContext(m_Display, visualInfo, nullptr, GL_TRUE);
		glXMakeCurrent(m_Display, m_Window, m_Context);
		
		HT_WARN("GL version: %s",                   reinterpret_cast<const char*>(glGetString(GL_VERSION)));
		HT_WARN("GL vendor: %s",                    reinterpret_cast<const char*>(glGetString(GL_VENDOR)));
		HT_WARN("GL renderer: %s",                  reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
		HT_WARN("GL shading language version: %s",  reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION)));
		
		if(!GLInit()) {
			HT_FATAL("%s", "[GLContext] Could not initialize GL");
		}
	}

	Context::~Context() {
		glXMakeCurrent(m_Display, None, nullptr);
		glXDestroyContext(m_Display, m_Context);
	}

	void Context::Update() {
		glXSwapBuffers(m_Display, m_Window);
	}

#endif // HT_LINUX

	void Context::Clear() {
		GL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	}

	void Context::Resize(u32 width, u32 height) {
		glViewport(0, 0, width, height);
	}

} }

#endif // HT_OPENGL