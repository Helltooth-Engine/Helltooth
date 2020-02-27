#pragma once

#include "Component.hpp"
#include "graphics/Texture.hpp"

namespace ht { namespace entities {
	
	class TextureComponent : public Component {
		HT_RTTI(TextureComponent, Component)

	private:
		graphics::Texture* m_Texture;

	public:
		inline TextureComponent(graphics::Texture* texture) : m_Texture(texture) { }
		inline ~TextureComponent() { }

		inline graphics::Texture* GetTexture() const { return m_Texture; }
	};

} }