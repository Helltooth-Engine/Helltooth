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

#if defined(HT_OPENGL)
#include "platform/opengl/GL.hpp"
#elif defined(HT_DIRECTX)
#include "platform/directx/DX.hpp"
#endif // HT_OPENGL

#include "core/Internal.hpp"

#include "graphics/Enums.hpp"

namespace ht { namespace graphics {

	class IndexBuffer {
	private:
		u32 m_Count;

#if defined(HT_OPENGL)
		u32 m_IndexBuffer;
		GLenum m_Format;
#elif defined(HT_DIRECTX)
		ID3D11Buffer* m_IndexBuffer;
		DXGI_FORMAT m_Format;
#endif // HT_OPENGL

	public:
		IndexBuffer(const u32* indices, u32 indexCount, BufferUsage usage);
		IndexBuffer(const u16* indices, u32 indexCount, BufferUsage usage);
		~IndexBuffer();

		void Bind() const;

#if defined(HT_OPENGL)
		inline GLenum GetFormat() const { return m_Format; }
#elif defined(HT_DIRECTX)
		inline DXGI_FORMAT GetFormat() const { return m_Format; }
#endif // HT_OPENGL

		inline u32 GetCount() const { return m_Count; }

	};

} }