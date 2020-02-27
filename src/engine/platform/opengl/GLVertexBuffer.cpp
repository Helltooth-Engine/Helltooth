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

	void* VertexBuffer::Map(BufferMapType mapType) {
		Bind();
		void* data = GL(glMapBuffer(GL_ARRAY_BUFFER, static_cast<GLenum>(mapType)));
		return data;
	}

	void VertexBuffer::Unmap() {
		GL(glUnmapBuffer(GL_ARRAY_BUFFER));
	}

	void VertexBuffer::Bind(u32 stride) const {
		GL(glBindBuffer(GL_ARRAY_BUFFER, m_Buffer));
	}

} }

#endif // HT_OPENGL