#pragma once

#include "Internal.hpp"

#include "cereal/Cereal.hpp"

#include "graphics/Texture.hpp"
#include "graphics/Texture2D.hpp"

#include "utils/String.hpp"
#include "utils/Vfs.hpp"

namespace ht { namespace core {

	class Asset {
	public:
		static graphics::Texture* LoadTexture(utils::String path);
	};

} }