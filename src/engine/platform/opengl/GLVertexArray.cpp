#ifdef HT_OPENGL
#include "graphics/buffers/VertexArray.hpp"

namespace ht { namespace graphics {

	VertexArray::VertexArray(BufferLayout layout) : m_Layout(layout) {
		
	}

	VertexArray::~VertexArray() {
		GL(glDeleteVertexArrays(1, &m_Array));
	}

	void VertexArray::Bind() {
		GL(glBindVertexArray(m_Array));
	}


} }


#endif