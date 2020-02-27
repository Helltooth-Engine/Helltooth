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
#include "graphics/Texture2D.hpp"

namespace ht { namespace graphics {

	void Texture2D::SetSamplerState() {
		GL(glGenerateMipmap(GL_TEXTURE_2D));
		GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,  GL_NEAREST));
		GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,  GL_LINEAR_MIPMAP_LINEAR));
		GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,      GL_REPEAT));
		GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,      GL_REPEAT));
		GL(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS,    0.4f));
	}

	Texture2D::Texture2D(u32 width, u32 height, TextureFormat format) : Texture(width, height, TextureType::TEXTURE_2D, format) {
		GL(glGenTextures(1, &m_Texture));
		GL(glBindTexture(GL_TEXTURE_2D, m_Texture));
		GL(glTexImage2D(GL_TEXTURE_2D, 0, static_cast<GLenum>(format), width, height, 0, static_cast<GLenum>(GetBaseFormat(format)), GL_UNSIGNED_BYTE, nullptr));
		SetSamplerState();
	}

	Texture2D::Texture2D(byte* pixels, u32 width, u32 height, TextureFormat format) : Texture(width, height, TextureType::TEXTURE_2D, format) {
		GL(glGenTextures(1, &m_Texture));
		GL(glBindTexture(GL_TEXTURE_2D, m_Texture));
		GL(glTexImage2D(GL_TEXTURE_2D, 0, static_cast<GLenum>(format), width, height, 0, static_cast<GLenum>(GetBaseFormat(format)), GL_UNSIGNED_BYTE, pixels));
		SetSamplerState();
	}

	Texture2D::~Texture2D() {
		GL(glDeleteTextures(1, &m_Texture));
	}

	void Texture2D::SetPixels(byte* pixels) {
		GL(glBindTexture(GL_TEXTURE_2D, m_Texture));
		GL(glTexImage2D(GL_TEXTURE_2D, 0, static_cast<GLenum>(m_Format), m_Width, m_Height, 0, static_cast<GLenum>(GetBaseFormat(m_Format)), GL_UNSIGNED_BYTE, pixels));
	}

	void Texture2D::Bind(u32 slot) const {
		GL(glBindTexture(GL_TEXTURE_2D, m_Texture));
		GL(glActiveTexture(GL_TEXTURE0 + slot));
	}

} }

#endif // HT_OPENGL