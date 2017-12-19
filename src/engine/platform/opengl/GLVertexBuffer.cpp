#ifdef HT_OPENGL
#include "graphics/buffers/VertexBuffer.hpp"

namespace ht { namespace graphics {

	VertexBuffer::VertexBuffer(const void* data, unsigned int size, unsigned int stride, BufferUsage usage) {
		glGenBuffers(1, &m_Buffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_Buffer);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, size, GL_FLOAT, GL_FALSE, stride, data);
	}

	VertexBuffer::~VertexBuffer() {
		glDeleteBuffers(1, &m_Buffer);
	}

	void VertexBuffer::Bind() const {
		glBindBuffer(GL_ARRAY_BUFFER, m_Buffer);
	}

} }


#endif