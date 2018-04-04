#ifdef HT_DIRECTX
#include "graphics/buffers/IndexBuffer.hpp"

namespace ht { namespace graphics {

	IndexBuffer::IndexBuffer(const u32* indices, u32 indexCount, BufferUsage usage)
		: m_Count(indexCount), m_Format(DXGI_FORMAT_R32_UINT) {
		D3D11_BUFFER_DESC bd = {};
		bd.Usage      = static_cast<D3D11_USAGE>(usage);
		bd.ByteWidth  = indexCount * sizeof(u32);
		bd.BindFlags  = D3D11_BIND_INDEX_BUFFER;

		D3D11_SUBRESOURCE_DATA data = {};
		data.pSysMem  = indices;
		DX(HT_DXDEVICE->CreateBuffer(&bd, &data, &m_IndexBuffer));
	}

	IndexBuffer::IndexBuffer(const u16* indices, u32 indexCount, BufferUsage usage)
		: m_Count(indexCount), m_Format(DXGI_FORMAT_R16_UINT) {
		D3D11_BUFFER_DESC bd = {};
		bd.Usage      = static_cast<D3D11_USAGE>(usage);
		bd.ByteWidth  = indexCount * sizeof(u32);
		bd.BindFlags  = D3D11_BIND_INDEX_BUFFER;

		D3D11_SUBRESOURCE_DATA data = {};
		data.pSysMem  = indices;
		DX(HT_DXDEVICE->CreateBuffer(&bd, &data, &m_IndexBuffer));
	}

	IndexBuffer::~IndexBuffer() {
		m_IndexBuffer->Release();
	}

	void IndexBuffer::Bind() {
		HT_DXCONTEXT->IASetIndexBuffer(m_IndexBuffer, m_Format, 0);
	}

} }

#endif // HT_DIRECTX