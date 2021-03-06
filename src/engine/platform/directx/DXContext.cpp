﻿/*
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

#ifdef HT_DIRECTX
#include "graphics/Context.hpp"

namespace ht { namespace graphics {

	Context::Context(HWND& hwnd) {
		RECT size;
		GetWindowRect(hwnd, &size);

		DXGI_SWAP_CHAIN_DESC sd = {};

		sd.BufferCount                         = 1;
		sd.BufferDesc.Width                    = size.right - size.left;
		sd.BufferDesc.Height                   = size.bottom - size.top;
		sd.BufferDesc.Format                   = DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.BufferDesc.RefreshRate.Numerator    = 60;
		sd.BufferDesc.RefreshRate.Denominator  = 1;
		sd.BufferUsage                         = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.OutputWindow                        = hwnd;
		sd.SampleDesc.Count                    = 1;
		sd.SampleDesc.Quality                  = 0;
		sd.Windowed                            = true;
		
		const D3D_FEATURE_LEVEL lvl[] = { 
			D3D_FEATURE_LEVEL_11_1, 
			D3D_FEATURE_LEVEL_11_0,
		};
		UINT createDeviceFlags = 0;
		D3D_FEATURE_LEVEL FeatureLevelIsSupprted;

#if defined(HT_DEBUG)
		createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif // HT_DEBUG

		m_Device = nullptr;
		DX(D3D11CreateDeviceAndSwapChain(0, D3D_DRIVER_TYPE_HARDWARE, 0, createDeviceFlags, lvl, _countof(lvl), D3D11_SDK_VERSION, &sd, &m_SwapChain, &m_Device, &FeatureLevelIsSupprted, &m_Context));
		
		ID3D11Texture2D* tmp = nullptr;
		m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&tmp);
		m_Device->CreateRenderTargetView(tmp, 0, &m_RenderTarget);
		tmp->Release();

		D3D11_TEXTURE2D_DESC td = {};

		td.Width               = size.right - size.left;
		td.Height              = size.bottom - size.top;
		td.MipLevels           = 1;
		td.ArraySize           = 1;
		td.Format              = DXGI_FORMAT_D32_FLOAT;
		td.Usage               = D3D11_USAGE_DEFAULT;
		td.BindFlags           = D3D11_BIND_DEPTH_STENCIL;
		td.SampleDesc.Count    = 1;
		td.SampleDesc.Quality  = 0;

		DX(m_Device->CreateTexture2D(&td, 0, &m_DepthStencilBuffer));

		D3D11_DEPTH_STENCIL_VIEW_DESC dsd = {};

		dsd.ViewDimension  = D3D11_DSV_DIMENSION_TEXTURE2D;
		dsd.Format         = DXGI_FORMAT_D32_FLOAT;

		DX(m_Device->CreateDepthStencilView(m_DepthStencilBuffer, &dsd, &m_DepthStencilView));

		m_Context->OMSetRenderTargets(1, &m_RenderTarget, m_DepthStencilView);

		D3D11_VIEWPORT v = {};

		v.TopLeftX  = 0;
		v.TopLeftY  = 0;
		v.Width     = static_cast<float>(size.right - size.left);
		v.Height    = static_cast<float>(size.bottom - size.top);
		v.MinDepth  = 0.0f;
		v.MaxDepth  = 1.0f;

		D3D11_RASTERIZER_DESC rd = {};

		rd.FillMode               = D3D11_FILL_SOLID;
		rd.CullMode               = D3D11_CULL_BACK;
		rd.FrontCounterClockwise  = true;
		rd.DepthClipEnable        = true;

		DX(m_Device->CreateRasterizerState(&rd, &m_RasterizerState));
		m_Context->RSSetState(m_RasterizerState);

		m_Context->RSSetViewports(1, &v);
		m_Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}

	Context::~Context() {
		m_Device->Release();
		m_Context->Release();
		m_SwapChain->Release();
		m_DepthStencilBuffer->Release();
		m_DepthStencilView->Release();
		m_RasterizerState->Release();
	}

	void Context::Resize(u32 width, u32 height) {
		D3D11_VIEWPORT v = {};

		v.TopLeftX       = 0;
		v.TopLeftY       = 0;
		v.Width          = width;
		v.Height         = height;
		v.MinDepth       = 0.0f;
		v.MaxDepth       = 1.0f;

		m_Context->RSSetViewports(1, &v);
	}


	void Context::Update() {
		DX(m_SwapChain->Present(0, 0));
	}

	void Context::Clear() {
		static float col[4]{ 0.3f,0.4f,0.7f,1.f };
		m_Context->ClearRenderTargetView(m_RenderTarget, col);
		m_Context->ClearDepthStencilView(m_DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
	}

} }

#endif // HT_DIRECTX