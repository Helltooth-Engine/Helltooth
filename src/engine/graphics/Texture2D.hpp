#pragma once

#if defined(HT_OPENGL)
#include "platform/opengl/GL.hpp"
#elif defined(HT_DIRECTX)
#include "platform/directx/DX.hpp"
#endif // HT_OPENGL

#include "core/Internal.hpp"

#include "graphics/Enums.hpp"
#include "graphics/Texture.hpp"

namespace ht { namespace graphics {

	class Texture2D : public Texture {
	private:
#if defined(HT_DIRECTX)
		ID3D11Texture2D* m_Texture;
#endif // HT_DIRECTX

	public:
		Texture2D(u32 width, u32 height, TextureFormat format);
		Texture2D(byte* pixels, u32 width, u32 height, TextureFormat format);
		~Texture2D();

		void SetPixels(byte* pixels);

		void Bind(u32 slot) const override;
	
	private:
		void SetSamplerState();
	};

} }