#ifdef HT_DIRECTX
#include "graphics/Context.hpp"

namespace ht { namespace graphics {

	Context::Context(HWND& hwnd) {
		RECT size;
		GetWindowRect(hwnd, &size);

		DXGI_SWAP_CHAIN_DESC sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.BufferCount = 1;
		sd.BufferDesc.Width = size.right - size.left;
		sd.BufferDesc.Height = size.bottom - size.top;
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.BufferDesc.RefreshRate.Numerator = 60;
		sd.BufferDesc.RefreshRate.Denominator = 1;
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.OutputWindow = hwnd;
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
		sd.Windowed = TRUE;
		
		const D3D_FEATURE_LEVEL lvl[] = { 
			D3D_FEATURE_LEVEL_11_1, 
			D3D_FEATURE_LEVEL_11_0,
		};
		UINT createDeviceFlags = 0;
		D3D_FEATURE_LEVEL FeatureLevelIsSupprted;
#ifdef HT_DEBUG
		createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
		m_Device = nullptr;
		D3D11CreateDeviceAndSwapChain(0, D3D_DRIVER_TYPE_HARDWARE, 0, createDeviceFlags, lvl, _countof(lvl), D3D11_SDK_VERSION,
			&sd, &m_SwapChain, &m_Device, &FeatureLevelIsSupprted, &m_Context);
		ID3D11Texture2D* tmp = nullptr;
		m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&tmp);
		m_Device->CreateRenderTargetView(tmp, 0, &m_RenderTarget);
		tmp->Release();

		D3D11_TEXTURE2D_DESC td;
		ZeroMemory(&td, sizeof(D3D11_TEXTURE2D_DESC));
		td.ArraySize = 1;
		td.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		td.Format = DXGI_FORMAT_D32_FLOAT;
		td.Width = size.right - size.left;
		td.Height = size.bottom - size.top;
		td.SampleDesc.Count = 1;
		td.SampleDesc.Quality = 0;

		m_Device->CreateTexture2D(&td, 0, &tmp);
		D3D11_DEPTH_STENCIL_VIEW_DESC dsd;
		ZeroMemory(&dsd, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
		dsd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		dsd.Format = DXGI_FORMAT_D32_FLOAT;

		m_Device->CreateDepthStencilView(tmp, &dsd, &m_DepthStencilView);
		tmp->Release();
		m_Context->OMSetRenderTargets(1, &m_RenderTarget, m_DepthStencilView);
	}

	Context::~Context() {
		m_Device->Release();

	}

	void Context::Update() {
		m_SwapChain->Present(0, 0);
	}

	void Context::Clear() {
		static float col[4]{ 0.3f,0.4f,0.7f,1.f };
		m_Context->ClearRenderTargetView(m_RenderTarget, col);
		m_Context->ClearDepthStencilView(m_DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
	}

} }


#endif