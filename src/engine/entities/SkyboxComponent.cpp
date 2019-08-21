#include "SkyboxComponent.hpp"

namespace ht { namespace entities {

	SkyboxComponent::SkyboxComponent(graphics::Texture* texture) {
		HT_ASSERT(texture != nullptr, "[SkyboxComponent] Texture cannot be null.");
		HT_ASSERT(texture->GetType() != graphics::TextureType::TEXTURE_3D, "[SkyboxComponent] Texture needs to be 3D.");
		m_TextureCube = static_cast<graphics::TextureCube*>(texture);
	}

} }