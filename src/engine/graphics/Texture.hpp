#pragma once

#include "core/Internal.hpp"

#include "graphics/Enums.hpp"
namespace ht { namespace graphics {

	class Texture {
	protected:
		u32 m_Width;
		u32 m_Height;
		TextureFormat m_Format = TextureFormat::UNKNOWN;
		TextureType m_Type = TextureType::UNKNOWN;
#if defined(HT_OPENGL)
		u32 m_Texture;
#endif
	protected:
		Texture(u32 width, u32 height, TextureType type) : m_Width(width), m_Height(height), m_Type(type) {}
		Texture(u32 width, u32 height, TextureType type, TextureFormat format) : m_Width(width), m_Height(height), m_Type(type), m_Format(format) {}
	public:
		virtual void Bind() = 0;
	};


} }