#ifdef HT_DIRECTX
#include "graphics/shaders/Shader.hpp"
#include "DX.hpp"

namespace ht { namespace graphics {
	using namespace core;
	using namespace utils;


	Shader::Shader(BufferLayout layout, String vertexPath, String fragmentPath, bool path) : m_Layout(layout) {
		UINT flag = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef HT_DEBUG
		flag |= D3DCOMPILE_DEBUG;
#endif
		char* vertex, *fragment;
		u32 vSize, fSize;
		if (path) {
			String vertexData = FileUtils::ReadFile(VFS::Resolve(vertexPath));
			String fragmentData = FileUtils::ReadFile(VFS::Resolve(fragmentPath));
			vSize = vertexData.GetSize() + 1;
			fSize = fragmentData.GetSize() + 1;

			vertex = new char[vSize];
			memcpy(vertex, vertexData.GetData(), vSize);

			fragment = new char[fSize];
			memcpy(fragment, fragmentData.GetData(), fSize);

		}
		else {
			vSize = vertexPath.GetSize() + 1;
			fSize = fragmentPath.GetSize() + 1;
			vertex = new char[vSize];
			fragment = new char[fSize];
			memcpy(vertex, vertexPath.GetData(), vSize);
			memcpy(fragment, fragmentPath.GetData(), fSize);
		}

		ID3DBlob* vertexShaderBlob = nullptr, *vertexErrorBlob = nullptr;
		DX(D3DCompile(vertex, vSize, NULL, NULL, NULL, "main", "vs_5_0", flag, 0, &vertexShaderBlob, &vertexErrorBlob));
		if (vertexErrorBlob) {
			HT_WARN("Vertex shader errors: \n%s", (const char*)vertexErrorBlob->GetBufferPointer());
			vertexErrorBlob->Release();
		}

		std::vector<D3D11_INPUT_ELEMENT_DESC> elementDescs;

		for (u32 i = 0; i < layout.attributes.size(); i++) {
			D3D11_INPUT_ELEMENT_DESC current = {};
			current.SemanticIndex = 0;
			current.SemanticName = layout.attributes[i].semanticName.GetData();
			current.Format = DXGI_FORMAT_R32G32_FLOAT;
			current.InputSlot = 0;
			current.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
			current.InstanceDataStepRate = 0;
			elementDescs.push_back(current);
		}

		DX(DIRECTX_DEVICE->CreateVertexShader(vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize(), NULL, &m_VertexShader));

		ID3DBlob* fragmentShaderBlob = nullptr, *fragmentErrorBlob = nullptr;

		DX(D3DCompile(fragment, fSize, NULL, NULL, NULL, "main", "ps_5_0", flag, 0, &fragmentShaderBlob, &fragmentErrorBlob));
		if (fragmentErrorBlob) {
			HT_WARN("Fragment shader errors: \n%s", (const char*)fragmentErrorBlob->GetBufferPointer());
			fragmentErrorBlob->Release();
		}
		DX(DIRECTX_DEVICE->CreatePixelShader(fragmentShaderBlob->GetBufferPointer(), fragmentShaderBlob->GetBufferSize(), NULL, &m_FragmentShader));


		for (BufferAttribute attrib : layout.attributes)
			m_Stride += attrib.stride * DataTypeSize(attrib.type);
		
		DX(DIRECTX_DEVICE->CreateInputLayout(&elementDescs[0], elementDescs.size(), vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize(), &m_InputLayout));
	
		vertexShaderBlob->Release();
		fragmentShaderBlob->Release();
	}

	Shader::~Shader() {
		m_VertexShader->Release();
		m_FragmentShader->Release();
	}

	void Shader::SetUniformBuffer(UniformBuffer* buffer) {

	}

	void Shader::Start() {
		DIRECTX_CONTEXT->VSSetShader(m_VertexShader, nullptr, 0);
		DIRECTX_CONTEXT->PSSetShader(m_FragmentShader, nullptr, 0);
		DIRECTX_CONTEXT->IASetInputLayout(m_InputLayout);
	}

} }

#endif