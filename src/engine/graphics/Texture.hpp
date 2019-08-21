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
		virtual void Bind(u32 slot) = 0;

		inline TextureType GetType() { return m_Type; }

	private:
		virtual void SetSamplerState() = 0;
	};

} }