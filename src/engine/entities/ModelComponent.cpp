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

#include "ModelComponent.hpp"

namespace ht { namespace entities {
	using namespace graphics;

	ModelComponent::ModelComponent(const void* vertices, u32 verticesSize) {
		m_VertexBuffer = new VertexBuffer(vertices, verticesSize, BufferUsage::STATIC);
	}

	ModelComponent::~ModelComponent() {
		delete m_VertexBuffer;
		delete m_IndexBuffer;
	}

	void ModelComponent::Bind(u32 stride) const {
		HT_ASSERT(m_IndexBuffer, "[ModelComponent] No index buffer found!");
		m_VertexBuffer->Bind(stride);
		m_IndexBuffer->Bind();
	}

	void ModelComponent::Render() const{
		HT_ASSERT(m_IndexBuffer, "[ModelComponent] No index buffer found!");
#if defined(HT_OPENGL)
		glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), m_IndexBuffer->GetFormat(), 0);
#elif defined(HT_DIRECTX)
		HT_DXCONTEXT->DrawIndexed(m_IndexBuffer->GetCount(), 0, 0);
#endif
	}

} }