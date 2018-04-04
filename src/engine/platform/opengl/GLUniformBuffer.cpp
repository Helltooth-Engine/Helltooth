#ifdef HT_OPENGL
#include "graphics/buffers/UniformBuffer.hpp"

namespace ht { namespace graphics {

	UniformBuffer::UniformBuffer(UniformBufferLayout layout, BufferUsage usage) : m_Layout(layout) {
		for (u32 i = 0; i < layout.attributes.size(); i++)
			m_Size += DataTypeSize(layout.attributes[i]);

		HT_ASSERT(m_Size % 4 == 0, "[UniformBuffer] Layout not multiple of 4");

		for (u32 i = 0; i < m_Size / sizeof(f32); i++)
			m_Data.push_back(0.0f);

		GL(glGenBuffers(1, &m_Buffer));
		GL(glBindBuffer(GL_UNIFORM_BUFFER, m_Buffer));
		GL(glNamedBufferData(m_Buffer, m_Size, &m_Data[0], GL_STREAM_DRAW));
		GL(glBindBuffer(GL_UNIFORM_BUFFER, 0));
	}

	UniformBuffer::~UniformBuffer() {
		GL(glDeleteBuffers(1, &m_Buffer));
	}

	void UniformBuffer::Set(u32 index, void* data) {
		u32 dataLocation = 0;
		for (u32 i = 0; i < index; i++)
			dataLocation += DataTypeSize(m_Layout.attributes[i]) / sizeof(f32);

		u32 size = DataTypeSize(m_Layout.attributes[index]);

		f32* bufferData = static_cast<f32*>(data);
		memcpy(static_cast<void*>(&m_Data[0] + dataLocation), static_cast<void*>(bufferData), size);
	}

	void UniformBuffer::Bind() {
		GL(glBindBuffer(GL_UNIFORM_BUFFER, m_Buffer));
		void* data = glMapBuffer(GL_UNIFORM_BUFFER, GL_WRITE_ONLY);
		memcpy(data, &m_Data[0], m_Size);
		glUnmapBuffer(GL_UNIFORM_BUFFER);

		switch (m_Layout.type) {
		case ShaderType::VERTEX:
			GL(glBindBufferBase(GL_UNIFORM_BUFFER, 0, m_Buffer));
			break;
		case ShaderType::FRAGMENT:
			GL(glBindBufferBase(GL_UNIFORM_BUFFER, 1, m_Buffer));
			break;
		}
	}

} }

#endif // HT_OPENGL