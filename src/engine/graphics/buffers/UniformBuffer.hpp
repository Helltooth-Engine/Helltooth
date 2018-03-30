#pragma once

#if defined(HT_OPENGL)
#include "platform/opengl/GL.hpp"
#elif defined(HT_DIRECTX)
#include "platform/directx/DX.hpp"
#endif // HT_OPENGL

#include "graphics/Enums.hpp"

#include "maths/Vector2.hpp"
#include "maths/Vector3.hpp"
#include "maths/Vector4.hpp"
#include "maths/Matrix4.hpp"

#include "utils/String.hpp"

namespace ht { namespace graphics {

	struct UniformBufferLayout {
		std::vector<DataType> attributes;
		ShaderType type;

		UniformBufferLayout(ShaderType type) : type(type) {}
		
		template<typename T>
		inline void AddUniform();
	};

	template<typename T>
	inline void UniformBufferLayout::AddUniform() {
		HT_ASSERT(true, "[UniformBufferLayout] Data type not recognized.");
	}

	template<>
	inline void UniformBufferLayout::AddUniform<f32>() {
		attributes.push_back(DataType::FLOAT);
	}

	template<>
	inline void UniformBufferLayout::AddUniform<maths::Vector2>() {
		attributes.push_back(DataType::VECTOR2);
	}
	
	template<>
	inline void UniformBufferLayout::AddUniform<maths::Vector3>() {
		attributes.push_back(DataType::VECTOR3);
	}
	
	template<>
	inline void UniformBufferLayout::AddUniform<maths::Vector4>() {
		attributes.push_back(DataType::VECTOR4);
	}
	
	template<>
	inline void UniformBufferLayout::AddUniform<maths::Matrix4>() {
		attributes.push_back(DataType::MATRIX4);
	}

	class UniformBuffer {
	private:
		UniformBufferLayout m_Layout;
		std::vector<f32> m_Data;
		u32 m_Size = 0;

#if defined(HT_OPENGL)
		u32 m_Buffer;
#elif defined(HT_DIRECTX)
		ID3D11Buffer* m_Buffer;
#endif // HT_OPENGL

	public:
		UniformBuffer(UniformBufferLayout layout, BufferUsage usage = BufferUsage::DYNAMIC);
		~UniformBuffer();

		void Set(u32 index, void* data);
		void Bind();

		inline ShaderType GetShaderType() { return m_Layout.type; }
	};

} }