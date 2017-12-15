#ifdef HT_OPENGL
#include "graphics/Context.hpp"
#include "platform/opengl/GL.hpp"

#include <gl/GL.h>

namespace ht { namespace graphics {

	Context::Context(HWND& hwnd) {
		PIXELFORMATDESCRIPTOR pfd;
		ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));
		pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		pfd.nVersion =	 1;
		pfd.dwFlags		= PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		pfd.iPixelType	= PFD_TYPE_RGBA;
		pfd.cColorBits	= 32;
		pfd.cDepthBits	= 32;
		pfd.iLayerType	= PFD_MAIN_PLANE;

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

		int attribs[] =
		{
			WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
			WGL_CONTEXT_MINOR_VERSION_ARB, 1,
			WGL_CONTEXT_FLAGS_ARB, 0,
			0
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
		
		HT_WARN("GL version: %s", (const char*)glGetString(GL_VERSION));
		HT_WARN("GL vendor: %s", (const char*)glGetString(GL_VENDOR));
		HT_WARN("GL renderer: %s", (const char*)glGetString(GL_RENDERER));
		HT_WARN("GL shading language version: %s", (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION));

		if (!GLInit()) {
			DWORD err = GetLastError(); 
			HT_FATAL("[GLContext] Could not initialize GL, %d!", err);
		}
	}

	Context::~Context() {
		wglMakeCurrent(m_DeviceContext, NULL);
		wglDeleteContext(m_Context);
	}

	void Context::Update() {
		SwapBuffers(m_DeviceContext);
	}

	void Context::Clear() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

} }
#endif