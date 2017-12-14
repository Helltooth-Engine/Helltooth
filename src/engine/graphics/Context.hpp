#include <Windows.h>
#include <stdio.h>

namespace ht { namespace graphics {

	class Context {
	private:
		HGLRC m_Context;
		HDC m_DeviceContext;

	public:
		Context(HWND hwnd);
		~Context();
	};

} }
