#pragma once

#include <vector>

#include "core/Internal.hpp"

#include "maths/Vector2.hpp"
#include "maths/Vector3.hpp"
#include "maths/Vector4.hpp"
#include "maths/Matrix4.hpp"

#include "graphics/Enums.hpp"

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

	struct UniformBufferLayout {
		std::vector<DataType> attributes;

		template<typename T>
		void AddUniform() {
			HT_ASSERT(true, "[UniformBufferLayout] Data type not recognized.");
		}

		template<>
		void AddUniform<f32>() {
			attributes.push_back(DataType::FLOAT);
		}

		template<>
		void AddUniform<maths::Vector2>() {
			attributes.push_back(DataType::VECTOR2);
		}
		template<>
		void AddUniform<maths::Vector3>() {
			attributes.push_back(DataType::VECTOR3);
		}
		template<>
		void AddUniform<maths::Vector4>() {
			attributes.push_back(DataType::VECTOR4);
		}

		template<>
		void AddUniform<maths::Matrix4>() {
			attributes.push_back(DataType::MATRIX4);
		}


	};

} }