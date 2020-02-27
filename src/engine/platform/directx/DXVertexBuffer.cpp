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

#ifdef HT_DIRECTX
#include "graphics/buffers/VertexBuffer.hpp"

namespace ht { namespace graphics {
	using namespace core;

	VertexBuffer::VertexBuffer(const void* data, u32 size, BufferUsage usage) {
		D3D11_BUFFER_DESC bd = {};

		bd.Usage           = (D3D11_USAGE)usage;
		bd.ByteWidth       = size;
		bd.BindFlags       = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags  = usage == BufferUsage::DYNAMIC ? D3D11_CPU_ACCESS_WRITE : 0;
		
		bool created = false;

		if (data == nullptr) {
			data = new char[size];
			created = true;
		}

		D3D11_SUBRESOURCE_DATA rd = {};

		rd.pSysMem = data;

		DX(HT_DXDEVICE->CreateBuffer(&bd, &rd, &m_Buffer));
		if (created)
			delete[] data;
	}

	VertexBuffer::~VertexBuffer() {
		m_Buffer->Release();
	}

	void* VertexBuffer::Map(BufferMapType mapType) {
		DX(HT_DXCONTEXT->Map(m_Buffer, 0, static_cast<D3D11_MAP>(mapType), 0, &m_MappedBuffer));
		return m_MappedBuffer.pData;
	}

	void VertexBuffer::Unmap() {
		HT_DXCONTEXT->Unmap(m_Buffer, 0);
	}

	void VertexBuffer::Bind(u32 stride) const {
		HT_ASSERT(stride, "[VertexBuffer] Stride can't be 0!");
		static u32 offset = 0;
		HT_DXCONTEXT->IASetVertexBuffers(0, 1, &m_Buffer, &stride, &offset);
	}

} }

#endif // HT_DIRECTX