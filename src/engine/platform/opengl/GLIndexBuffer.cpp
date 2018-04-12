#ifdef HT_OPENGL
#include "graphics/buffers/IndexBuffer.hpp"

namespace ht { namespace graphics {

	IndexBuffer::IndexBuffer(const u32* indices, u32 indexCount, BufferUsage usage) 
		: m_Count(indexCount / sizeof(u32)), m_Format(GL_UNSIGNED_INT) {
		GL(glGenBuffers(1, &m_IndexBuffer));
		GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer));
		GL(glNamedBufferData(m_IndexBuffer, indexCount, indices, static_cast<GLenum>(usage)));
		GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}

	IndexBuffer::IndexBuffer(const u16* indices, u32 indexCount, BufferUsage usage) 
		: m_Count(indexCount / sizeof(u32)), m_Format(GL_UNSIGNED_SHORT) {
		GL(glGenBuffers(1, &m_IndexBuffer));
		GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer));
		GL(glNamedBufferData(m_IndexBuffer, indexCount, indices, static_cast<GLenum>(usage)));
		GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}

	IndexBuffer::~IndexBuffer() {
		GL(glDeleteBuffers(1, &m_IndexBuffer));
	}

	void IndexBuffer::Bind() const {
		GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer));
	}

} }

#endif // HT_OPENGL