#pragma once

#include "entities/Component.hpp"

#include "graphics/TextureCube.hpp"


namespace ht { namespace entities {

	class SkyboxComponent : public Component {
		HT_RTTI(SkyboxComponent, Component)
	private:
		graphics::TextureCube* m_TextureCube;

	public:
		SkyboxComponent(graphics::Texture* texture);

		inline graphics::TextureCube* GetTexture() const { return m_TextureCube; }
	};

} }