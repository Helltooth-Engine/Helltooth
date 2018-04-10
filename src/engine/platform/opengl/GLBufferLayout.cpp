#ifdef HT_OPENGL
#include "graphics/buffers/BufferLayout.hpp"

namespace ht { namespace graphics {

	BufferLayout::BufferLayout(){
		GL(glGenVertexArrays(1, &m_VaoID));
	}

	BufferLayout::~BufferLayout() {
		GL(glDeleteVertexArrays(1, &m_VaoID));
	}

	void BufferLayout::Init(void* shaderBlob) { }

	void BufferLayout::Bind(VertexBuffer** buffers) {
		glBindVertexArray(m_VaoID);
		u32 attribOffset = 0;
		u32 offset = 0;
		if (buffers != nullptr) {
			buffers[0]->Bind();
		}
		int lastBuffer = 0;
		for (u32 i = 0; i < m_Attributes.size(); i++) {
			if (m_Attributes[i + attribOffset].bufferId != lastBuffer) {
				lastBuffer = m_Attributes[i + attribOffset].bufferId;
				offset = 0;
				buffers[lastBuffer]->Bind();
			}
			if (m_Attributes[i + attribOffset].type == DataType::MATRIX4) {
				u8 dataSize = DataTypeSize(DataType::FLOAT);
				for (int k = 0; k < 4; k++, attribOffset++) {
					GL(glEnableVertexAttribArray(i + attribOffset));
					GL(glVertexAttribPointer(i + attribOffset, m_Attributes[i].count / 4, static_cast<GLenum>(DataType::FLOAT), static_cast<GLboolean>(m_Attributes[i + attribOffset].normalized), m_Stride[lastBuffer], reinterpret_cast<GLvoid*>(offset)));
					offset += m_Attributes[i + attribOffset].count * dataSize;
				}
			}
			else {
				u8 dataSize = DataTypeSize(m_Attributes[i].type);
				GL(glEnableVertexAttribArray(i + attribOffset));
				GL(glVertexAttribPointer(i + attribOffset, m_Attributes[i + attribOffset].count, static_cast<GLenum>(m_Attributes[i + attribOffset].type), static_cast<GLboolean>(m_Attributes[i + attribOffset].normalized), m_Stride[lastBuffer], reinterpret_cast<GLvoid*>(offset)));
				offset += m_Attributes[i + attribOffset].count * dataSize;
			}
		}
	}

} }

#endif // HT_OPENGL