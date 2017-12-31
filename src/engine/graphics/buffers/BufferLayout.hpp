#pragma once

#include <vector>

#include "core/Internal.hpp"

#include "maths/Vector2.hpp"
#include "maths/Vector3.hpp"
#include "maths/Vector4.hpp"
#include "maths/Matrix4.hpp"

#include "graphics/Enums.hpp"

#include "utils/String.hpp"

namespace ht { namespace graphics {

	struct BufferAttribute {
		utils::String semanticName;
		DataType type;
		u16 count;
		u16 stride;
		bool normalized;
	};

	struct BufferLayout {
		std::vector<BufferAttribute> attributes;

		template<typename T>
		void AddLayout(utils::String semanticName, u16 count, u16 stride, bool normalized) {
			HT_ASSERT(true, "[BufferLayout] Data type not recognized.");
		}

		template<>
		void AddLayout<f32>(utils::String semanticName, u16 count, u16 stride, bool normalized) {
			attributes.push_back({ semanticName, DataType::FLOAT, count, stride, normalized });
		}

		template<>
		void AddLayout<u16>(utils::String semanticName, u16 count, u16 stride, bool normalized) {
			attributes.push_back({ semanticName, DataType::UNSIGNED_SHORT, count, stride, normalized });
		}

		template<>
		void AddLayout<u32>(utils::String semanticName, u16 count, u16 stride, bool normalized) {
			attributes.push_back({ semanticName, DataType::UNSIGNED_INT, count, stride, normalized });
		}
	};

} }