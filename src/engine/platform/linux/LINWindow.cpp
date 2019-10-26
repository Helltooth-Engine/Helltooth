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
		
		s32 screen = DefaultScreen(m_Display);
		XID rootWindow = RootWindow(m_Display, screen);

		int attribs[] = {
			GLX_X_RENDERABLE, 	True,
			GLX_DRAWABLE_TYPE, 	GLX_WINDOW_BIT,
			GLX_RENDER_TYPE, 	GLX_RGBA_BIT,
			GLX_X_VISUAL_TYPE,	GLX_TRUE_COLOR,
			GLX_RED_SIZE,		8,
			GLX_GREEN_SIZE,		8,
			GLX_BLUE_SIZE,		8,
			GLX_ALPHA_SIZE,		8,
			GLX_DEPTH_SIZE,		24,
			GLX_STENCIL_SIZE,	8,
			GLX_DOUBLEBUFFER,	True,
			None
		};

		s32 major, minor;
		if (!glXQueryVersion(m_Display, &major, &minor)) {
			HT_FATAL("%s", "[GLContext] Could not query glX version");
			return;
		}
		if (major < 1 || (major == 1 && minor < 3)) {
			HT_FATAL("%s", "[GLContext] glX version too low!");
			return;
		}

		s32 fbConfigCount = 0;
		GLXFBConfig* fbConfigs = glXChooseFBConfig(m_Display, DefaultScreen(m_Display), attribs, &fbConfigCount);
		if (!fbConfigs) {
			HT_FATAL("%s", "[GLContext] Could not create fbConfigs");
			return;
		}
		
		if (fbConfigCount == 0) {
			HT_FATAL("%s", "[GLContext] FB Config Count can not be 0");
			return;
		}

		s32 bestFbConfigIndex = 0, bestSampleCount = 0;
		for (s32 i = 0; i < fbConfigCount; i++) {
			XVisualInfo* vi = glXGetVisualFromFBConfig(m_Display, fbConfigs[i]);
			if (vi) {
				int samples = 0, sampleCount = 0;
				glXGetFBConfigAttrib(m_Display, fbConfigs[i], GLX_SAMPLE_BUFFERS, &samples);
				glXGetFBConfigAttrib(m_Display, fbConfigs[i], GLX_SAMPLES, &sampleCount);

				if(samples && sampleCount > bestSampleCount) {
					bestFbConfigIndex = i;
					bestSampleCount = sampleCount;
				}
			}
			XFree(vi);
		}

		GLXFBConfig bestFbConfig = fbConfigs[bestFbConfigIndex];

		XFree(fbConfigs);

		XVisualInfo* vi = glXGetVisualFromFBConfig(m_Display, bestFbConfig);
		
		Colormap colormap = XCreateColormap(m_Display, rootWindow, vi->visual, AllocNone);
		
		XSetWindowAttributes windowAttribs = {};
		windowAttribs.colormap = colormap;
		windowAttribs.background_pixmap = None;
		windowAttribs.border_pixel = 0;
		windowAttribs.event_mask = StructureNotifyMask;

		m_Window = XCreateWindow(m_Display, rootWindow, 0, 0, width, height, 0, vi->depth, InputOutput, vi->visual, CWColormap | CWEventMask, &windowAttribs);
		
		XMapWindow(m_Display, m_Window);
		XStoreName(m_Display, m_Window, m_Title.c_str());

		m_Context = new graphics::Context(m_Display, m_Window, bestFbConfig);

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
