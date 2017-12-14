#ifdef HT_OPENGL
#include "graphics/Context.hpp"


namespace ht { namespace graphics {

	Context::Context(HWND hwnd) {
		PIXELFORMATDESCRIPTOR pfd =
		{
			sizeof(PIXELFORMATDESCRIPTOR),
			1,
			PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
			PFD_TYPE_RGBA,
			32,
			0, 0, 0, 0, 0, 0,
			0,
			0,
			0,
			0, 0, 0, 0,
			24,
			8,
			0,
			PFD_MAIN_PLANE,
			0,
			0, 0, 0
		};
		m_DeviceContext = GetDC(hwnd);
		int pixelFormat;
		if ((pixelFormat = ChoosePixelFormat(m_DeviceContext, &pfd) == 0)) {
			//TODO: proper logging
			printf("Could not choose pixel format.");
			return;
		}

		SetPixelFormat(m_DeviceContext, pixelFormat, &pfd);
		m_Context = wglCreateContext(m_DeviceContext);
		wglMakeCurrent(m_DeviceContext, m_Context);
	}

	Context::~Context() {
		wglMakeCurrent(m_DeviceContext, NULL);
		wglDeleteContext(m_Context);
	}

} }
#endif