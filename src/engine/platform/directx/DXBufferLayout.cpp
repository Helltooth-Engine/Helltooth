#ifdef HT_DIRECTX
#include "graphics/buffers/BufferLayout.hpp"

namespace ht { namespace graphics {

	BufferLayout::BufferLayout() { }
	BufferLayout::~BufferLayout() { m_InputLayout->Release(); }

	void BufferLayout::Init(void* shaderBlob) {
		ID3DBlob* shader = static_cast<ID3DBlob*>(shaderBlob);

		std::vector<D3D11_INPUT_ELEMENT_DESC> elementDescs;

		u32 attribOffset = 0;
		u32 lastBuffer = -1;

		for (u32 i = 0; i < m_Attributes.size(); i++) {
			D3D11_INPUT_ELEMENT_DESC current = {};
			current.SemanticName  = m_Attributes[i + attribOffset].semanticName.GetData();

			if (m_Attributes[i + attribOffset].type == DataType::MATRIX4) {
				for (int k = 0; k < 4; k++, attribOffset++) {
					current.SemanticIndex = k;
					current.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
					current.InputSlot = m_Attributes[i + attribOffset].bufferId;
					current.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
					current.InstanceDataStepRate = 0;
					if (lastBuffer != m_Attributes[i + attribOffset].bufferId) {
						lastBuffer = m_Attributes[i + attribOffset].bufferId;
						current.AlignedByteOffset = 0;
					}
					else {
						current.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
					}
					elementDescs.push_back(current);
				}
			}
			else {
				current.SemanticIndex = 0;
				if (static_cast<DXGI_FORMAT>(m_Attributes[i + attribOffset].type) == DXGI_FORMAT_R32_FLOAT) {
					switch (m_Attributes[i + attribOffset].count) {
					case 1:
						current.Format = DXGI_FORMAT_R32_FLOAT;
						break;
					case 2:
						current.Format = DXGI_FORMAT_R32G32_FLOAT;
						break;
					case 3:
						current.Format = DXGI_FORMAT_R32G32B32_FLOAT;
						break;
					case 4:
						current.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
						break;
					default:
						HT_ASSERT(false, "[BufferLayout] Attribute count not supported.");
					}
				}
				else {
					current.Format = static_cast<DXGI_FORMAT>(m_Attributes[i + attribOffset].type);
				}

				current.InputSlot = m_Attributes[i + attribOffset].bufferId;
				current.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
				current.InstanceDataStepRate = 0;
				if (lastBuffer != m_Attributes[i + attribOffset].bufferId) {
					lastBuffer = m_Attributes[i + attribOffset].bufferId;
					current.AlignedByteOffset = 0;
				}
				else {
					current.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
				}
				elementDescs.push_back(current);
			}
		}

		DX(HT_DXDEVICE->CreateInputLayout(&elementDescs[0], elementDescs.size(), shader->GetBufferPointer(), shader->GetBufferSize(), &m_InputLayout));
	}

	void BufferLayout::Bind(VertexBuffer** buffers) {
		HT_DXCONTEXT->IASetInputLayout(m_InputLayout);
	}

} }

#endif // HT_DIRECTX