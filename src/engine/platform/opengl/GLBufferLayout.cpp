#ifdef HT_OPENGL
#include "graphics/buffers/BufferLayout.hpp"

namespace ht { namespace graphics {

	BufferLayout::BufferLayout() : m_Stride(0) {
		GL(glGenVertexArrays(1, &m_VaoID));
	}

	BufferLayout::~BufferLayout() {
		GL(glDeleteVertexArrays(1, &m_VaoID));
	}

	void BufferLayout::Init(void* shaderBlob) { }

	void BufferLayout::Start() {
		glBindVertexArray(m_VaoID);
		u32 offset = 0;
		for (u32 i = 0; i < m_Attributes.size(); i++) {
			u8 dataSize = DataTypeSize(m_Attributes[i].type);
			GL(glEnableVertexAttribArray(i));
			GL(glVertexAttribPointer(i, m_Attributes[i].count, static_cast<GLenum>(m_Attributes[i].type), static_cast<GLboolean>(m_Attributes[i].normalized), m_Stride, reinterpret_cast<GLvoid*>(offset)));
			offset += m_Attributes[i].count * dataSize;
		}
	}

} }

#endif