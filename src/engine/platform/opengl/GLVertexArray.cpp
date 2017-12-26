#ifdef HT_OPENGL
#include "graphics/buffers/VertexArray.hpp"

namespace ht { namespace graphics {

	VertexArray::VertexArray(BufferLayout layout) : m_Layout(layout) {
		HT_ASSERT(layout.attributes.size() > 10, "[VertexBuffer] Layout attributes can not be bigger than 10!");
		GL(glGenVertexArrays(1, &m_Array));
		GL(glBindVertexArray(m_Array));

		u32 offset = 0;
		for (u32 i = 0; i < layout.attributes.size(); i++) {
			u8 dataSize = DataTypeSize(layout.attributes[i].type);
			GL(glEnableVertexAttribArray(i));
			GL(glVertexAttribPointer(i, layout.attributes[i].count, (GLenum)layout.attributes[i].type,
				(GLboolean)layout.attributes[i].normalized, layout.attributes[i].stride * dataSize, (GLvoid*)offset));
			offset += layout.attributes[i].count * dataSize;
		}
		GL(glBindVertexArray(0));
	}

	VertexArray::~VertexArray() {
		GL(glDeleteVertexArrays(1, &m_Array));
	}

	void VertexArray::Bind() {
		GL(glBindVertexArray(m_Array));
	}


} }


#endif