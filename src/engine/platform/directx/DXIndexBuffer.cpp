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
#include "graphics/buffers/IndexBuffer.hpp"

namespace ht { namespace graphics {

	IndexBuffer::IndexBuffer(const u32* indices, u32 indexCount, BufferUsage usage)
		: m_Count(indexCount / sizeof(u32)), m_Format(DXGI_FORMAT_R32_UINT) {
		D3D11_BUFFER_DESC bd = {};
		bd.Usage      = static_cast<D3D11_USAGE>(usage);
		bd.ByteWidth  = indexCount;
		bd.BindFlags  = D3D11_BIND_INDEX_BUFFER;

		D3D11_SUBRESOURCE_DATA data = {};
		data.pSysMem  = indices;
		DX(HT_DXDEVICE->CreateBuffer(&bd, &data, &m_IndexBuffer));
	}

	IndexBuffer::IndexBuffer(const u16* indices, u32 indexCount, BufferUsage usage)
		: m_Count(indexCount / sizeof(u32)), m_Format(DXGI_FORMAT_R16_UINT) {
		D3D11_BUFFER_DESC bd = {};
		bd.Usage      = static_cast<D3D11_USAGE>(usage);
		bd.ByteWidth  = indexCount;
		bd.BindFlags  = D3D11_BIND_INDEX_BUFFER;

		D3D11_SUBRESOURCE_DATA data = {};
		data.pSysMem  = indices;
		DX(HT_DXDEVICE->CreateBuffer(&bd, &data, &m_IndexBuffer));
	}

	IndexBuffer::~IndexBuffer() {
		m_IndexBuffer->Release();
	}

	void IndexBuffer::Bind() const{
		HT_DXCONTEXT->IASetIndexBuffer(m_IndexBuffer, m_Format, 0);
	}

} }

#endif // HT_DIRECTX