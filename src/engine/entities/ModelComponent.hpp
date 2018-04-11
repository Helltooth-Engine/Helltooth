#pragma once

#include "Component.hpp"

#include "graphics/buffers/BufferLayout.hpp"
#include "graphics/buffers/VertexBuffer.hpp"
#include "graphics/buffers/IndexBuffer.hpp"

namespace ht { namespace entities {

	class ModelComponent : public Component {
		HT_RTTI(ModelComponent, Component)

	private:
		graphics::VertexBuffer* m_VertexBuffer;
		graphics::IndexBuffer* m_IndexBuffer = nullptr;

	public:
		ModelComponent(const void* vertices, u32 verticesSize);
		~ModelComponent();

		void Bind(u32 stride = 0) const;
		void Render() const;

		template <typename T>
		inline void SetIndices(const T* indices, u32 indicesSize) {
			HT_ASSERT(false, "Indices format not supported.");
		}

		graphics::IndexBuffer* GetIndexBuffer() { return m_IndexBuffer; }

	};

	template <>
	inline void ModelComponent::SetIndices<u16>(const u16* indices, u32 indicesSize) {
		m_IndexBuffer = new graphics::IndexBuffer(indices, indicesSize, graphics::BufferUsage::STATIC);
	}

	template <>
	inline void ModelComponent::SetIndices<u32>(const u32* indices, u32 indicesSize) {
		m_IndexBuffer = new graphics::IndexBuffer(indices, indicesSize, graphics::BufferUsage::STATIC);
	}

} }