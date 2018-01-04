#ifdef HT_OPENGL
#include "graphics/Texture2D.hpp"

namespace ht { namespace graphics {

	Texture2D::Texture2D(u32 width, u32 height, TextureFormat format) : Texture(width, height, TextureType::TEXTURE_2D, format) {
		glGenTextures(1, &m_Texture);
		glBindTexture(GL_TEXTURE_2D, m_Texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexImage2D(GL_TEXTURE_2D, 0, (GLenum)format, width, height, 0, (GLenum)format, GL_UNSIGNED_BYTE, nullptr);
	}

	Texture2D::Texture2D(byte* pixels, u32 width, u32 height, TextureFormat format) : Texture(width, height, TextureType::TEXTURE_2D, format) {
		glGenTextures(1, &m_Texture);
		glBindTexture(GL_TEXTURE_2D, m_Texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexImage2D(GL_TEXTURE_2D, 0, (GLenum)format, width, height, 0, (GLenum)format, GL_UNSIGNED_BYTE, pixels);
	}

	Texture2D::~Texture2D() {
		glDeleteTextures(1, &m_Texture);
	}

	void Texture2D::SetPixels(byte* pixels) {
		glBindTexture(GL_TEXTURE_2D, m_Texture);
		glTexImage2D(GL_TEXTURE_2D, 0, (GLenum)m_Format, m_Width, m_Height, 0, (GLenum)m_Format, GL_UNSIGNED_BYTE, pixels);
	}

	void Texture2D::Bind() {
		glBindTexture(GL_TEXTURE_2D, m_Texture);
	}


} }


#endif