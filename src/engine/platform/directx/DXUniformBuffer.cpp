#ifdef HT_DIRECTX

#include "graphics/buffers/UniformBuffer.hpp"

namespace ht { namespace graphics {
	using namespace core;

	UniformBuffer::UniformBuffer(UniformBufferLayout layout, BufferUsage usage) : m_Layout(layout) {
		for (u32 i = 0; i < layout.attributes.size; i++)
			m_Size += DataTypeSize(layout.attributes[i]);
		
		HT_ASSERT(m_Size % 16 != 0, "[UniformBuffer] Layout not 16 byte aligned");

		for (u32 i = 0; i < m_Size / sizeof(f32); i++)
			m_Data.push_back(0.0f);

		D3D11_BUFFER_DESC bd = {};
		bd.Usage = (D3D11_USAGE)usage;
		bd.ByteWidth = m_Size;
		bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		D3D11_SUBRESOURCE_DATA rd = {};
		rd.pSysMem = &m_Data[0];

		Window::GetWindow()->GetDevice()->CreateBuffer(&bd, &rd, &m_Buffer);
	}

	UniformBuffer::~UniformBuffer() {
		m_Buffer->Release();
	}

	void UniformBuffer::Set(u32 index, void* data) {
		u32 dataLocation = 0;
		for (u32 i = 0; i < index; i++)
			dataLocation += DataTypeSize(m_Layout.attributes[i]) / sizeof(f32);
		
		u32 size = DataTypeSize(m_Layout.attributes[index]);

		f32* bufferData = (f32*)data;
		memcpy((void*)(&m_Data[0] + dataLocation), (void*)bufferData, size);
	}

} }


#endif