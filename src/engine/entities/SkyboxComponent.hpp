#pragma once

#include "entities/Component.hpp"

#include "graphics/TextureCube.hpp"


namespace ht { namespace entities {

	class SkyboxComponent : public Component {
		HT_RTTI(SkyboxComponent, Component)
	private:
		graphics::TextureCube* m_TextureCube;

	public:
		SkyboxComponent(graphics::TextureCube* textureCube = nullptr);

		graphics::TextureCube* GetTexture() { return m_TextureCube; }
	};

} }