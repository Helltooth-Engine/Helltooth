#ifdef HT_DIRECTX
#include "graphics/buffers/VertexBuffer.hpp"

namespace ht { namespace graphics {
	using namespace core;

	VertexBuffer::VertexBuffer(const void* data, u32 size, BufferUsage usage) {
		D3D11_BUFFER_DESC bd = {};

		bd.Usage      = (D3D11_USAGE)usage;
		bd.ByteWidth  = size;
		bd.BindFlags  = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA rd = {};
		rd.pSysMem    = data;
		
		DX(HT_DXDEVICE->CreateBuffer(&bd, &rd, &m_Buffer));
	}

	VertexBuffer::~VertexBuffer() {
		m_Buffer->Release();
	}

	void* VertexBuffer::Map(BufferMapType mapType) {
		DX(HT_DXCONTEXT->Map(m_Buffer, 0, static_cast<D3D11_MAP>(mapType), 0, &m_MappedBuffer));
		return m_MappedBuffer.pData;
	}

	void VertexBuffer::Unmap() {
		HT_DXCONTEXT->Unmap(m_Buffer, 0);
	}

	void VertexBuffer::Bind(u32 stride) const {
		static u32 offset = 0;
		HT_DXCONTEXT->IASetVertexBuffers(0, 1, &m_Buffer, &stride, &offset);
	}

} }

#endif // HT_DIRECTX