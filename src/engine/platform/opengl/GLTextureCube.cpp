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
#include "graphics/TextureCube.hpp"

namespace ht { namespace graphics {

	void TextureCube::SetSamplerState() {
		GL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER,  GL_LINEAR));
		GL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER,  GL_LINEAR));
		GL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S,      GL_CLAMP_TO_EDGE));
		GL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T,      GL_CLAMP_TO_EDGE));
		GL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R,      GL_CLAMP_TO_EDGE));
	}

	TextureCube::TextureCube(u32 width, u32 height, TextureFormat format)
		: Texture(width, height, TextureType::TEXTURE_3D, format) {
		GL(glGenTextures(1, &m_Texture));
		GL(glBindTexture(GL_TEXTURE_CUBE_MAP, m_Texture));

		SetSamplerState();
	}

	TextureCube::TextureCube(byte** pixels, u32 width, u32 height, TextureFormat format)
		: Texture(width, height, TextureType::TEXTURE_3D, format) {
		GL(glGenTextures(1, &m_Texture));
		GL(glBindTexture(GL_TEXTURE_CUBE_MAP, m_Texture));

		for (u32 i = 0; i < 6; i++) {
			GL(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, static_cast<GLenum>(format), width, height, 0, static_cast<GLenum>(GetBaseFormat(format)), GL_UNSIGNED_BYTE, pixels[i]));
		}

		SetSamplerState();
	}

	TextureCube::~TextureCube() {
		GL(glDeleteTextures(1, &m_Texture));
	}

	void TextureCube::SetPixels(byte** pixels) {
		GL(glBindTexture(GL_TEXTURE_CUBE_MAP, m_Texture));
		for (u32 i = 0; i < 6; i++) {
			GL(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, static_cast<GLenum>(m_Format), m_Width, m_Height, 0, static_cast<GLenum>(GetBaseFormat(m_Format)), GL_UNSIGNED_BYTE, pixels[i]));
		}
	}

	void TextureCube::Bind(u32 slot) const {
		GL(glBindTexture(GL_TEXTURE_CUBE_MAP, m_Texture));
		GL(glActiveTexture(GL_TEXTURE0 + slot));
	}

} }

#endif // HT_OPENGL