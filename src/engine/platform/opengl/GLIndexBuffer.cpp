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