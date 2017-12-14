#ifdef HT_OPENGL
#include "graphics/Context.hpp"
#include "platform/opengl/GL.hpp"

namespace ht { namespace graphics {

	Context::Context(HWND hwnd) {
		PIXELFORMATDESCRIPTOR pfd;
		ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));
		pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		pfd.nVersion = 1;
		pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		pfd.iPixelType = PFD_TYPE_RGBA;
		pfd.cColorBits = 24;
		pfd.cDepthBits = 24;
		pfd.iLayerType = PFD_MAIN_PLANE;

		m_DeviceContext = GetDC(hwnd);
		int pixelFormat = ChoosePixelFormat(m_DeviceContext, &pfd);
		if (pixelFormat == 0) {
			//TODO: proper logging
			printf("Could not choose pixel format.");
			return;
		}

		SetPixelFormat(m_DeviceContext, pixelFormat, &pfd);
		m_Context = wglCreateContext(m_DeviceContext);
		if (!wglMakeCurrent(m_DeviceContext, m_Context)) {
			DWORD err = GetLastError();
			printf("Could not create context, %d !", err);
			return;
		}

		if (!GLInit()) {
			printf("Could not initialize GL!");
		}
	}

	Context::~Context() {
		wglMakeCurrent(m_DeviceContext, NULL);
		wglDeleteContext(m_Context);
	}

	void Context::Update() {

	}

	void Context::Clear() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

} }
#endif