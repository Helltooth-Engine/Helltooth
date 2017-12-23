#ifdef HT_OPENGL

#include "graphics/buffers/UniformBuffer.hpp"

namespace ht { namespace graphics {

	UniformBuffer::UniformBuffer(UniformBufferLayout layout, BufferUsage usage) : m_Layout(layout) {
		for (u32 i = 0; i < layout.attributes.size(); i++)
			m_Size += DataTypeSize(layout.attributes[i]);

		HT_ASSERT(m_Size % 4 != 0, "[UniformBuffer] Layout not multiple of 4");

		for (u32 i = 0; i < m_Size / sizeof(f32); i++)
			m_Data.push_back(0.0f);
		
		glGenBuffers(1, &m_Buffer);
		glBindBuffer(GL_UNIFORM_BUFFER, m_Buffer);
		glBufferData(GL_UNIFORM_BUFFER, m_Size, &m_Data[0], (GLenum)usage);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

	UniformBuffer::~UniformBuffer() {
		glDeleteBuffers(1, &m_Buffer);
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