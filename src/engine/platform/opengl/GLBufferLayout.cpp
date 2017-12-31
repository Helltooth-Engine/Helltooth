#ifdef HT_OPENGL

#include "graphics/buffers/BufferLayout.hpp"

namespace ht { namespace graphics {

	BufferLayout::BufferLayout() {
		glGenVertexArrays(1, &m_VaoID);
	}

	BufferLayout::~BufferLayout() {
		glDeleteVertexArrays(1, &m_VaoID);
	}

	void BufferLayout::Init(void* shaderBlob) {
		//nothing
	}

	void BufferLayout::Start() {
		glBindVertexArray(m_VaoID);
		u32 offset = 0;
		for (u32 i = 0; i < m_Attributes.size(); i++) {
			u8 dataSize = DataTypeSize(m_Attributes[i].type);
			GL(glEnableVertexAttribArray(i));
			GL(glVertexAttribPointer(i, m_Attributes[i].count, (GLenum)m_Attributes[i].type,
				(GLboolean)m_Attributes[i].normalized, m_Attributes[i].stride * dataSize, (GLvoid*)offset));
			offset += m_Attributes[i].count * dataSize;
		}
	}


} }

#endif