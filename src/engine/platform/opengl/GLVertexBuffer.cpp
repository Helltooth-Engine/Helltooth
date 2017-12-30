#ifdef HT_OPENGL
#include "graphics/buffers/VertexBuffer.hpp"

namespace ht { namespace graphics {

	VertexBuffer::VertexBuffer(const void* data, u32 size, BufferUsage usage) {
		GL(glGenBuffers(1, &m_Buffer));
		GL(glBindBuffer(GL_ARRAY_BUFFER, m_Buffer));
		GL(glNamedBufferData(m_Buffer, size, data, (GLenum)usage));
		GL(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}

	VertexBuffer::~VertexBuffer() {
		GL(glDeleteBuffers(1, &m_Buffer));
	}

	void VertexBuffer::Bind(u32 stride) const {
		GL(glBindBuffer(GL_ARRAY_BUFFER, m_Buffer));
	}

} }

#endif