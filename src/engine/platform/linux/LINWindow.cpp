#ifdef HT_LINUX
#include "core/Window.hpp"

namespace ht { namespace core {
	using namespace graphics;

	Window* Window::s_Window = nullptr;

	Window::Window(std::string title, u32 width, u32 height) 
		: m_Title(title), m_Width(width), m_Height(height) {
		m_Display = XOpenDisplay(nullptr);
		if (m_Display == nullptr) {
			HT_FATAL("%s", "[Window] Coult not connect to X Server.");
			return;
		}

		m_Window = DefaultRootWindow(m_Display);

#if defined(HT_OPENGL)
		m_Title.append(" - OpenGL");
#elif defined (HT_DIRECTX)
		m_Title.append(" - DirectX");
#endif

		m_Context = new Context(m_Display, m_Window);

		m_Window = XCreateWindow(m_Display, m_Window, 0, 0, width, height, 0, m_Context->GetVisualInfo()->depth, InputOutput,m_Context->GetVisualInfo()->visual, CWColormap | CWEventMask, m_Context->GetWindowAttributes());

		XMapWindow(m_Display, m_Window);

		XStoreName(m_Display, m_Window, title.c_str());

		s_Window = this;
	}

	Window::~Window() {
	
	}

	void Window::SetVisible(bool visible) {

	}

	void Window::Update() {

	}

	void Window::Clear() {

	}

	void Window::SetTitle(std::string title) {
		XStoreName(m_Display, m_Window, title.c_str());
	}

} }


#endif // HT_LINUX
