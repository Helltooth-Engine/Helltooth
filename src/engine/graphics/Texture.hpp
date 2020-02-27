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

#include "core/Internal.hpp"

#include "graphics/Enums.hpp"

namespace ht { namespace graphics {

	class Texture {
	protected:
		u32 m_Width;
		u32 m_Height;

		TextureFormat m_Format  = TextureFormat::UNKNOWN;
		TextureType m_Type      = TextureType::UNKNOWN;

#if defined(HT_OPENGL)
		u32 m_Texture;
#elif defined(HT_DIRECTX)
		ID3D11ShaderResourceView* m_ResourceView;
		ID3D11SamplerState* m_SamplerState;
#endif // HT_OPENGL

	protected:
		Texture(u32 width, u32 height, TextureType type) : m_Width(width), m_Height(height), m_Type(type) {}
		Texture(u32 width, u32 height, TextureType type, TextureFormat format) : m_Width(width), m_Height(height), m_Type(type), m_Format(format) {}

#ifdef HT_DIRECTX
		~Texture() {
			m_ResourceView->Release();
			m_SamplerState->Release();
		}
#endif // HT_DIRECTX


	public:
		virtual void Bind(u32 slot) const = 0;

		inline TextureType GetType() { return m_Type; }

	private:
		virtual void SetSamplerState() = 0;
	};

} }