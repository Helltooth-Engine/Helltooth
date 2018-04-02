#pragma once

#if defined(HT_DIRECTX)
#include <d3d11.h>
#include <d3d10.h>
#include <dxgi.h>
#elif defined(HT_OPENGL)
#include "platform/opengl/GL.hpp"
#endif // HT_DIRECTX

#if defined(HT_WINDOWS)
#include <Windows.h>
#elif defined(HT_LINUX)
#include <X11/X.h>
#include <X11/Xlib.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>
#endif // HT_WINDOWS

#include "utils/Log.hpp"

namespace ht { namespace graphics {

	class Context {
	private:
#if defined(HT_OPENGL)
#	if defined(HT_WINDOWS)
		HDC m_DeviceContext;
		HGLRC m_Context;
		HWND m_Hwnd;
#	elif defined(HT_LINUX)
		GLXContext m_Context;
		_XDisplay* m_Display;
#	endif // HT_WINDOWS
#elif defined(HT_DIRECTX)
		IDXGISwapChain* m_SwapChain;
		ID3D11Device* m_Device;
		ID3D11DeviceContext* m_Context;
		ID3D11RenderTargetView* m_RenderTarget;
		ID3D11DepthStencilView* m_DepthStencilView;
		ID3D11Texture2D* m_DepthStencilBuffer;
#endif // HT_OPENGL

	public:
#if defined(HT_WINDOWS)
		Context(HWND& hwnd);
#elif defined(HT_LINUX)
		Context(_XDisplay* display, XID& window, XVisualInfo* visualInfo);
#endif // HT_WINDOWS
		~Context();

		void Update();
		void Clear();

#if defined(HT_DIRECTX)
		inline ID3D11Device* GetDevice() { return m_Device; }
		inline ID3D11DeviceContext* GetDeviceContext() { return m_Context; }
#endif // HT_DIRECTX

	};

} }
