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

#ifdef HT_LINUX
#include "core/Window.hpp"

namespace ht { namespace core {
	using namespace graphics;

	Window* Window::s_Window = nullptr;

	Window::Window(std::string title, u32 width, u32 height) 
		: m_Title(title), m_Width(width), m_Height(height) {
#if defined(HT_OPENGL)
		m_Title.append(" - OpenGL");
#endif // HT_OPENGL
		m_Display = XOpenDisplay(nullptr);
		if (m_Display == nullptr) {
			HT_FATAL("%s", "[Window] Could not connect to X Server.");
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
		windowAttribs.event_mask = StructureNotifyMask | KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask | PointerMotionMask;

		m_Window = XCreateWindow(m_Display, rootWindow, 0, 0, width, height, 0, vi->depth, InputOutput, vi->visual, CWColormap | CWEventMask, &windowAttribs);
		
		m_WindowDestroyAtom = XInternAtom(m_Display, "WM_DELETE_WINDOW", True);
		XSetWMProtocols(m_Display, m_Window, &m_WindowDestroyAtom, 1);

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
		if (visible)
			XMapWindow(m_Display, m_Window);
		else
			XUnmapWindow(m_Display, m_Window);
	}

	void Window::Update() {
		while (XPending(m_Display)) {
			XEvent event;
			XNextEvent(m_Display, &event);
			HandleXEvent(event);
		}
		m_Context->Update();
	}

	void Window::Clear() {
		m_Context->Clear();
	}

	void Window::SetTitle(std::string title) {
#if defined(HT_OPENGL)
		title.append(" - OpenGL");
#endif // HT_OPENGL
		XStoreName(m_Display, m_Window, title.c_str());
	}

	void Window::HandleXEvent(const XEvent& event) {
		Window* window = Window::GetWindow();

		Event* e = new Event();
		bool inputEvent = false;

		switch (event.type) {
		case ClientMessage:
		{
			Atom atom = *reinterpret_cast<const Atom*>(event.xclient.data.l);
			if (atom == window->m_WindowDestroyAtom)
				window->m_ShouldClose = true;
			break;
		}
		case ButtonPress:
		case ButtonRelease:
			e->eventType                = EventType::MOUSE;
			e->mouse.mouseButton        = event.xbutton.button;
			e->mouse.mouseButtonState   = static_cast<State>(1 + (event.type == ButtonPress));
			e->mouse.x                  = event.xbutton.x;
			e->mouse.y                  = event.xbutton.y;
			inputEvent                  = true;
			break;
		case MotionNotify:
			e->eventType                = EventType::MOUSE;
			e->mouse.mouseButton        = -1;
			e->mouse.mouseButtonState   = State::NONE;
			e->mouse.x                  = event.xbutton.x;
			e->mouse.y                  = event.xbutton.y;
			inputEvent                  = true;
			break;
		case KeyPress:
		case KeyRelease:
			e->eventType                = EventType::KEYBOARD;
			e->key.key                  = event.xkey.keycode;
			e->key.modifiers            = static_cast<u16>(Modifier::NONE);
			e->key.state                = static_cast<State>(1 + (event.type == KeyPress));
			inputEvent                  = true;
			break;
		}

		if (inputEvent)
			EventDispatcher::Dispatch(e);

		delete e;
	}


} }

#endif // HT_LINUX
