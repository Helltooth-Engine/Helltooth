#pragma once

#if defined(HT_OPENGL)
#include "platform/opengl/GL.hpp"
#elif defined(HT_DIRECTX)
#include "platform/directx/DX.hpp"
#endif // HT_OPENGL

#include <vector>

#include "core/Internal.hpp"

#include "graphics/Enums.hpp"
#include "graphics/buffers/VertexBuffer.hpp"

#include "maths/Vector2.hpp"
#include "maths/Vector3.hpp"
#include "maths/Vector4.hpp"
#include "maths/Matrix4.hpp"

#include "utils/String.hpp"

namespace ht { namespace graphics {

	struct BufferAttribute {
		utils::String semanticName;
		DataType type;
		u16 count;
		bool normalized;
		bool instancing;
		u32 bufferId;
	};

	class BufferLayout {
	protected:
		std::vector<BufferAttribute> m_Attributes;

		std::vector<u32> m_Stride;

		u32 m_BuffersCount = 0;

#if defined(HT_OPENGL)
		u32 m_VaoID;
#elif defined(HT_DIRECTX)
		ID3D11InputLayout* m_InputLayout;
#endif // HT_OPENGL

	public:
		BufferLayout();
		~BufferLayout();

		void Bind(const VertexBuffer** buffers = nullptr);

		void Init(void* shaderBlob = nullptr);

		void SetSemanticNames(const std::vector<std::string>& semanticNames) {
			HT_ASSERT(semanticNames.size() <= m_Attributes.size(), "[BufferLayout] Too many semanticNames in the shader.");

			int semanticCount = 0;

			std::vector<BufferAttribute> newAttributes; // The new attributes are going to get here

			for (const std::string& semanticName : semanticNames) {
				for (u32 i = 0; i < m_Attributes.size(); i++) {
					if (utils::String(semanticName) == m_Attributes[i].semanticName) {
						newAttributes.push_back(m_Attributes[i]);
						semanticCount++;
						break;
					}
				}
			}
			m_Attributes = newAttributes;
		}

		inline u32 GetStride(u32 index = 0) { return m_Stride[index]; }

		template<typename T>
		inline void AddLayout(const utils::String& semanticName, u16 count, bool normalized, bool instancing = false, u32 bufferId = 0);

	};

	template<typename T>
	inline void BufferLayout::AddLayout(const utils::String& semanticName, u16 count, bool normalized, bool instancing, u32 bufferId) {
		HT_ASSERT(false, "[BufferLayout] Data type not recognized.");
	}

	template<>
	inline void BufferLayout::AddLayout<f32>(const utils::String& semanticName, u16 count, bool normalized, bool instancing, u32 bufferId) {
		m_Attributes.push_back({ semanticName, DataType::FLOAT, count, normalized, instancing, bufferId });
		m_BuffersCount = bufferId;
		if (m_Stride.size() <= bufferId)
			m_Stride.push_back(count * DataTypeSize(DataType::FLOAT));
		else
			m_Stride[bufferId] += count * DataTypeSize(DataType::FLOAT);
	}

	template<>
	inline void BufferLayout::AddLayout<u16>(const utils::String& semanticName, u16 count, bool normalized, bool instancing, u32 bufferId) {
		m_Attributes.push_back({ semanticName, DataType::UNSIGNED_SHORT, count, normalized, instancing, bufferId });
		m_BuffersCount = bufferId;
		if (m_Stride.size() <= bufferId)
			m_Stride.push_back(count * DataTypeSize(DataType::FLOAT));
		else
			m_Stride[bufferId] += count * DataTypeSize(DataType::FLOAT);
	}

	template<>
	inline void BufferLayout::AddLayout<u32>(const utils::String& semanticName, u16 count, bool normalized, bool instancing, u32 bufferId) {
		m_Attributes.push_back({ semanticName, DataType::UNSIGNED_INT, count, normalized, instancing, bufferId });
		m_BuffersCount = bufferId;
		if (m_Stride.size() <= bufferId)
			m_Stride.push_back(count * DataTypeSize(DataType::FLOAT));
		else
			m_Stride[bufferId] += count * DataTypeSize(DataType::FLOAT);
	}

	template<>
	inline void BufferLayout::AddLayout<maths::Matrix4>(const utils::String& semanticName, u16 count, bool normalized, bool instancing, u32 bufferId) {
		m_Attributes.push_back({semanticName, DataType::MATRIX4, count, normalized, instancing, bufferId });
		m_BuffersCount = bufferId;
		if (m_Stride.size() <= bufferId)
			m_Stride.push_back(count * DataTypeSize(DataType::MATRIX4));
		else
			m_Stride[bufferId] += count * DataTypeSize(DataType::MATRIX4);
	}

} }