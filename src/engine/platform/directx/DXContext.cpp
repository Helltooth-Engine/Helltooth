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
		UINT FeatureLevelIsSupprted;
#ifdef HT_DEBUG
		createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
		m_Device = nullptr;
		D3D11CreateDeviceAndSwapChain(0, D3D_DRIVER_TYPE_HARDWARE, 0, createDeviceFlags, lvl, _countof(lvl), D3D11_SDK_VERSION, &sd, &m_SwapChain, &m_Device, &FeatureLevelIsSupprted, &m_Context);
		
	}

	Context::~Context() {
		m_Device->Release();

	}

	void Context::Update() {

	}

	void Context::Clear() {

	}

} }


#endif