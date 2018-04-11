#include "ModelComponent.hpp"

namespace ht { namespace entities {
	using namespace graphics;

	ModelComponent::ModelComponent(const void* vertices, u32 verticesSize) {
		m_VertexBuffer = new VertexBuffer(vertices, verticesSize, BufferUsage::STATIC);
	}

	ModelComponent::~ModelComponent() {
		delete m_VertexBuffer;
		delete m_IndexBuffer;
	}

	void ModelComponent::Bind(u32 stride) const {
		HT_ASSERT(m_IndexBuffer, "[ModelComponent] No index buffer found!");
		m_VertexBuffer->Bind(stride);
		m_IndexBuffer->Bind();
	}

	void ModelComponent::Render() const{
		HT_ASSERT(m_IndexBuffer, "[ModelComponent] No index buffer found!");
#if defined(HT_OPENGL)
		glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), m_IndexBuffer->GetFormat(), 0);
#elif defined(HT_DIRECTX)
		HT_DXCONTEXT->DrawIndexed(m_IndexBuffer->GetCount(), 0, 0);
#endif
	}

} }