/*
 * Copyright (c) 2020 Rareș-Nicolaie Ciorbă
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

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

	void BufferLayout::Bind(const VertexBuffer** buffers) {
		GL(glBindVertexArray(m_VaoID));
		u32 attribOffset = 0;
		uptr offset = 0;
		if (buffers != nullptr) {
			buffers[0]->Bind();
		}
		int lastBuffer = 0;
		for (u32 i = 0; i < m_Attributes.size(); i++) {
			if (m_Attributes[i].bufferId != lastBuffer) {
				lastBuffer = m_Attributes[i].bufferId;
				offset = 0;
				buffers[lastBuffer]->Bind();
			}
			if (m_Attributes[i].type == DataType::MATRIX4) {
				u8 dataSize = DataTypeSize(DataType::FLOAT);
				for (int k = 0; k < 4; k++, attribOffset++) {
					GL(glEnableVertexAttribArray(i + attribOffset));
					GL(glVertexAttribPointer(i + attribOffset, 4, static_cast<GLenum>(DataType::FLOAT), static_cast<GLboolean>(m_Attributes[i].normalized), m_Stride[lastBuffer], reinterpret_cast<GLvoid*>(offset)));
					offset += 4 * dataSize;
					if (m_Attributes[i].instancing)
						GL(glVertexAttribDivisor(i + attribOffset, 1));
				}
			}
			else {
				u8 dataSize = DataTypeSize(m_Attributes[i].type);
				GL(glEnableVertexAttribArray(i + attribOffset));
				GL(glVertexAttribPointer(i + attribOffset, m_Attributes[i].count, static_cast<GLenum>(m_Attributes[i].type), static_cast<GLboolean>(m_Attributes[i].normalized), m_Stride[lastBuffer], reinterpret_cast<GLvoid*>(offset)));
				offset += m_Attributes[i].count * dataSize;
				if (m_Attributes[i].instancing)
					GL(glVertexAttribDivisor(i + attribOffset, 1));
			}
		}
	}

} }

#endif // HT_OPENGL