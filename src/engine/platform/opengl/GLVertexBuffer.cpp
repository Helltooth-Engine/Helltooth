#ifdef HT_OPENGL
#include "graphics/buffers/VertexBuffer.hpp"

namespace ht { namespace graphics {

	VertexBuffer::VertexBuffer(const void* data, u32 size, BufferLayout layout, BufferUsage usage): m_Layout(layout) {
		HT_ASSERT(layout.attributes.size() > 10, "[VertexBuffer] Layout attributes can not be bigger than 10!");

		GL(glGenBuffers(1, &m_Buffer));
		GL(glBindBuffer(GL_ARRAY_BUFFER, m_Buffer));


		u32 offset = 0;
		for (u32 i = 0; i < layout.attributes.size(); i++) {
			u8 dataSize = DataTypeSize(layout.attributes[i].type);
			GL(glEnableVertexAttribArray(i));
			GL(glVertexAttribPointer(i, layout.attributes[i].count, (GLenum)layout.attributes[i].type,
				(GLboolean)layout.attributes[i].normalized, layout.attributes[i].stride * dataSize, (GLvoid*)offset));
			offset += layout.attributes[i].count * dataSize;
		}
		
		GL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
	}

	VertexBuffer::~VertexBuffer() {
		GL(glDeleteBuffers(1, &m_Buffer));
	}

	void VertexBuffer::Bind() const {
		GL(glBindBuffer(GL_ARRAY_BUFFER, m_Buffer));
	}

} }

#endif