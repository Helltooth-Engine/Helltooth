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

#pragma once

#include "Component.hpp"

#include "graphics/buffers/BufferLayout.hpp"
#include "graphics/buffers/VertexBuffer.hpp"
#include "graphics/buffers/IndexBuffer.hpp"

namespace ht { namespace entities {

	class ModelComponent : public Component {
		HT_RTTI(ModelComponent, Component)

	private:
		graphics::VertexBuffer* m_VertexBuffer;
		graphics::IndexBuffer* m_IndexBuffer = nullptr;

	public:
		// verticesSize is the size in bytes
		ModelComponent(const void* vertices, u32 verticesSize);
		~ModelComponent();

		void Bind(u32 stride = 0) const;
		void Render() const;

		template <typename T>
		inline void SetIndices(const T* indices, u32 indicesSize) {
			HT_ASSERT(false, "Indices format not supported.");
		}

		inline const graphics::IndexBuffer*   GetIndexBuffer()   const { return m_IndexBuffer; }
		inline const graphics::VertexBuffer*  GetVertexBuffer()  const { return m_VertexBuffer; }
	};

	template <>
	inline void ModelComponent::SetIndices<u16>(const u16* indices, u32 indicesSize) {
		m_IndexBuffer = new graphics::IndexBuffer(indices, indicesSize, graphics::BufferUsage::STATIC);
	}

	template <>
	inline void ModelComponent::SetIndices<u32>(const u32* indices, u32 indicesSize) {
		m_IndexBuffer = new graphics::IndexBuffer(indices, indicesSize, graphics::BufferUsage::STATIC);
	}

} }