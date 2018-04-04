#ifdef HT_DIRECTX
#include "graphics/buffers/BufferLayout.hpp"

namespace ht { namespace graphics {

	BufferLayout::BufferLayout() { }
	BufferLayout::~BufferLayout() { m_InputLayout->Release(); }


	void BufferLayout::Init(void* shaderBlob) {
		ID3DBlob* shader = static_cast<ID3DBlob*>(shaderBlob);

		std::vector<D3D11_INPUT_ELEMENT_DESC> elementDescs;

		for (u32 i = 0; i < m_Attributes.size(); i++) {
			D3D11_INPUT_ELEMENT_DESC current = {};
			current.SemanticIndex = 0;
			current.SemanticName  = m_Attributes[i].semanticName.GetData();
			if (static_cast<DXGI_FORMAT>(m_Attributes[i].type) == DXGI_FORMAT_R32_FLOAT) {
				switch (m_Attributes[i].count) {
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
					HT_ASSERT(true, "[BufferLayout] Attribute count not supported.");
				}
			}
			else {
				current.Format = static_cast<DXGI_FORMAT>(m_Attributes[i].type);
			}

			current.InputSlot            = 0;
			current.InputSlotClass       = D3D11_INPUT_PER_VERTEX_DATA;
			current.InstanceDataStepRate = 0;
			current.AlignedByteOffset    = (i > 0) ? D3D11_APPEND_ALIGNED_ELEMENT : 0;
			elementDescs.push_back(current);
		}

		DX(HT_DXDEVICE->CreateInputLayout(&elementDescs[0], elementDescs.size(), shader->GetBufferPointer(), shader->GetBufferSize(), &m_InputLayout));
	}

	void BufferLayout::Bind() {
		HT_DXCONTEXT->IASetInputLayout(m_InputLayout);
	}

} }

#endif // HT_DIRECTX