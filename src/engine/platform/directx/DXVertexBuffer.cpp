#ifdef HT_DIRECTX
#include "graphics/buffers/VertexBuffer.hpp"
#include "core/Window.hpp"

namespace ht { namespace graphics {
	using namespace core;

	VertexBuffer::VertexBuffer(const void* data, u32 size, BufferLayout layout, BufferUsage usage): m_Layout(layout) {
		D3D11_BUFFER_DESC bd = {};
		bd.Usage = (D3D11_USAGE)usage;
		bd.ByteWidth = size;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA rd = {};
		rd.pSysMem = data;
		
		Window::GetWindow()->GetDevice()->CreateBuffer(&bd, &rd, &m_Buffer);
		m_Offset = 0;
		for (BufferAttribute attrib : layout.attributes)
			m_Stride += attrib.stride * DataTypeSize(attrib.type);
	}

	VertexBuffer::~VertexBuffer() {
		m_Buffer->Release();
	}

	void VertexBuffer::Bind() const {
		unsigned int offset = 0;
		Window::GetWindow()->GetDeviceContext()->IASetVertexBuffers(0, 1, &m_Buffer, &m_Stride, &m_Offset);
	}

} }
#endif