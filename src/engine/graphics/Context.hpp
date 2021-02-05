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
		HDC 						m_DeviceContext;
		HGLRC 						m_Context;
		HWND 						m_Hwnd;
#	elif defined(HT_LINUX)
		GLXContext 					m_Context;
		_XDisplay* 					m_Display;
		XID                         m_Window;
#	endif // HT_WINDOWS
#elif defined(HT_DIRECTX)
		IDXGISwapChain* 			m_SwapChain;
		ID3D11Device* 				m_Device;
		ID3D11DeviceContext* 		m_Context;
		ID3D11RenderTargetView* 	m_RenderTarget;
		ID3D11DepthStencilView* 	m_DepthStencilView;
		ID3D11Texture2D* 			m_DepthStencilBuffer;
		ID3D11RasterizerState* 		m_RasterizerState;
#endif // HT_OPENGL

	public:
#if defined(HT_WINDOWS)
		Context(HWND& hwnd);
#elif defined(HT_LINUX)
		Context(_XDisplay* display, XID& window, GLXFBConfig fbConfig);
#endif // HT_WINDOWS
		~Context();

		void Update();
		void Clear();

		void Resize(u32 width, u32 height);

#if defined(HT_DIRECTX)
		inline ID3D11Device* GetDevice() { return m_Device; }
		inline ID3D11DeviceContext* GetDeviceContext() { return m_Context; }
#endif // HT_DIRECTX

	};

} }