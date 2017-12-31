#ifdef HT_DIRECTX
#include "graphics/buffers/BufferLayout.hpp"

namespace ht { namespace graphics {

	BufferLayout::BufferLayout() {

	}

	BufferLayout::~BufferLayout() {
		m_InputLayout->Release();
	}

	void BufferLayout::Init(void* shaderBlob) {
		ID3DBlob* shader = (ID3DBlob*)shaderBlob;
		m_Stride = 0;
		for (BufferAttribute attrib : m_Attributes)
			m_Stride += attrib.stride * DataTypeSize(attrib.type);

		std::vector<D3D11_INPUT_ELEMENT_DESC> elementDescs;

		for (u32 i = 0; i < m_Attributes.size(); i++) {
			D3D11_INPUT_ELEMENT_DESC current = {};
			current.SemanticIndex = 0;
			current.SemanticName = m_Attributes[i].semanticName.GetData();
			if ((DXGI_FORMAT)m_Attributes[i].type == DXGI_FORMAT_R32_FLOAT) {
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
				}
			}
			else {
				current.Format = (DXGI_FORMAT)m_Attributes[i].type;
			}
			current.InputSlot = 0;
			current.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
			current.InstanceDataStepRate = 0;
			elementDescs.push_back(current);
		}

		DX(HT_DXDEVICE->CreateInputLayout(&elementDescs[0], elementDescs.size(),
			shader->GetBufferPointer(), shader->GetBufferSize(), &m_InputLayout));
	}

	void BufferLayout::Start() {
		HT_DXCONTEXT->IASetInputLayout(m_InputLayout);
	}

} }


#endif