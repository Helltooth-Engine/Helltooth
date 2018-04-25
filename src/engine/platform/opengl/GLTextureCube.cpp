#ifdef HT_OPENGL
#include "graphics/TextureCube.hpp"

namespace ht { namespace graphics {

	void TextureCube::SetSamplerState() {
		GL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER,  GL_LINEAR));
		GL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER,  GL_LINEAR));
		GL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S,      GL_REPEAT));
		GL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T,      GL_REPEAT));
		GL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R,      GL_REPEAT));
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
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, static_cast<GLenum>(format), width, height, 0, static_cast<GLenum>(GetBaseFormat(format)), GL_UNSIGNED_BYTE, pixels[i]);
		}

		SetSamplerState();
	}

	TextureCube::~TextureCube() {
		GL(glDeleteTextures(1, &m_Texture));
	}

	void TextureCube::SetPixels(byte** pixels) {
		GL(glBindTexture(GL_TEXTURE_CUBE_MAP, m_Texture));
		for (u32 i = 0; i < 6; i++) {
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, static_cast<GLenum>(format), width, height, 0, static_cast<GLenum>(GetBaseFormat(format)), GL_UNSIGNED_BYTE, pixels[i]);
		}
	}

	void TextureCube::Bind(u32 slot) {
		GL(glBindTexture(GL_TEXTURE_CUBE_MAP, m_Texture));
		GL(glActiveTexture(GL_TEXTURE0 + slot));
	}

} }

#endif // HT_OPENGL