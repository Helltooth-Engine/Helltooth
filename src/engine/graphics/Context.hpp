#pragma once
#include <Windows.h>
#include "utils/Log.hpp"

#ifdef HT_DIRECTX
#include <d3d11.h>
#include <d3d10.h>
#include <dxgi.h>
#endif

namespace ht { namespace graphics {

	class Context {
	private:
		HDC m_DeviceContext;
#ifdef HT_OPENGL
		HGLRC m_Context;
		HWND m_Hwnd;
#elif defined(HT_DIRECTX)
		IDXGISwapChain* m_SwapChain;
		ID3D11Device* m_Device;
		ID3D11DeviceContext* m_Context;
		ID3D11RenderTargetView* m_RenderTarget;
		ID3D11DepthStencilView* m_DepthStencilView;
#endif

	public:
		Context(HWND& hwnd);
		~Context();

		void Update();
		void Clear();
	};

} }
