#pragma once

#if defined(HT_OPENGL)
#include "platform/opengl/GL.hpp"
#elif defined(HT_DIRECTX)
#include "platform/directx/DX.hpp"
#endif

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

	class BufferLayout {
	private:
		std::vector<BufferAttribute> m_Attributes;

		u32 m_Stride = 0;

#if defined(HT_OPENGL)
		u32 m_VaoID;
#elif defined(HT_DIRECTX)
		ID3D11InputLayout* m_InputLayout;
#endif

	public:
		BufferLayout();
		~BufferLayout();

		void Start();

		void Init(void* shaderBlob = nullptr);

		template<typename T>
		void AddLayout(utils::String semanticName, u16 count, u16 stride, bool normalized) {
			HT_ASSERT(true, "[BufferLayout] Data type not recognized.");
		}

		template<>
		void AddLayout<f32>(utils::String semanticName, u16 count, u16 stride, bool normalized) {
			m_Attributes.push_back({ semanticName, DataType::FLOAT, count, stride, normalized });
			m_Stride += stride * DataTypeSize(DataType::FLOAT);
		}

		template<>
		void AddLayout<u16>(utils::String semanticName, u16 count, u16 stride, bool normalized) {
			m_Attributes.push_back({ semanticName, DataType::UNSIGNED_SHORT, count, stride, normalized });
			m_Stride += stride * DataTypeSize(DataType::UNSIGNED_SHORT);
		}

		template<>
		void AddLayout<u32>(utils::String semanticName, u16 count, u16 stride, bool normalized) {
			m_Attributes.push_back({ semanticName, DataType::UNSIGNED_INT, count, stride, normalized });
			m_Stride += stride * DataTypeSize(DataType::UNSIGNED_INT);
		}

		u32 GetStride() { return m_Stride; }
	};

} }