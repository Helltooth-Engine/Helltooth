#ifdef HT_DIRECTX
#include "graphics/buffers/VertexBuffer.hpp"
#include "core/Window.hpp"

namespace ht { namespace graphics {
	using namespace core;

	VertexBuffer::VertexBuffer(const void* data, unsigned int size, unsigned int stride, BufferUsage usage): stride(stride) {
		D3D11_BUFFER_DESC bd = {};
		bd.Usage = (D3D11_USAGE)usage;
		bd.ByteWidth = size;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		

		D3D11_SUBRESOURCE_DATA rd = {};
		rd.pSysMem = data;
		
		Window::GetWindow()->GetDevice()->CreateBuffer(&bd, &rd, &m_Buffer);
	}

	VertexBuffer::~VertexBuffer() {
		m_Buffer->Release();
	}

	void VertexBuffer::Bind() const {
		unsigned int offset = 0;
		Window::GetWindow()->GetDeviceContext()->IASetVertexBuffers(0, 1, &m_Buffer, &stride, &offset);
	}

} }
#endif