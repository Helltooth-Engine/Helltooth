#ifdef HT_LINUX
#include "core/Window.hpp"

namespace ht { namespace core {
	using namespace graphics;

	Window* Window::s_Window = nullptr;

	Window::Window(std::string title, u32 width, u32 height) 
		: m_Title(title), m_Width(width), m_Height(height) {
		m_Title.append(" - OpenGL");

		m_Display = XOpenDisplay(nullptr);
		if (m_Display == nullptr) {
			HT_FATAL("%s", "[Window] Coult not connect to X Server.");
			return;
		}

		XID rootWindow = DefaultRootWindow(m_Display);
		
		int attributes[] = {
			GLX_RGBA,
			GLX_DEPTH_SIZE, 24,
			GLX_DOUBLEBUFFER,
			None
		};
		
		m_VisualInfo = glXChooseVisual(m_Display, 0, attributes);
		if (m_VisualInfo == nullptr) {
			HT_FATAL("%s", "[Window] Could not select an appropriate visual");
			return;
		}
		else {
			HT_INFO("Visual %p selected!", m_VisualInfo->visualid);
		}

		m_Colormap = XCreateColormap(m_Display, rootWindow, m_VisualInfo->visual, AllocNone);

		XSetWindowAttributes windowAttribs = {};
		windowAttribs.colormap = m_Colormap;
		windowAttribs.event_mask = ExposureMask | KeyPressMask;

		m_Window = XCreateWindow(m_Display, rootWindow, 0, 0, width, height, 0, m_VisualInfo->depth, InputOutput, m_VisualInfo->visual, CWColormap | CWEventMask, &windowAttribs);
		
		XMapWindow(m_Display, m_Window);
		XStoreName(m_Display, m_Window, m_Title.c_str());

		m_Context = new graphics::Context(m_Display, m_Window, m_VisualInfo);

		s_Window = this;
	}

	Window::~Window() {
		delete m_Context;
		XDestroyWindow(m_Display, m_Window);
		XCloseDisplay(m_Display);
	}

	void Window::SetVisible(bool visible) {

	}

	void Window::Update() {
		m_Context->Update();
		glXSwapBuffers(m_Display, m_Window);
	}

	void Window::Clear() {
		m_Context->Clear();
	}

	void Window::SetTitle(std::string title) {
		XStoreName(m_Display, m_Window, title.c_str());
	}

} }

#endif // HT_LINUX
