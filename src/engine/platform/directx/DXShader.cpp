#ifdef HT_DIRECTX
#include "graphics/shaders/Shader.hpp"
#include "DX.hpp"

namespace ht { namespace graphics {
	using namespace core;
	using namespace utils;


	Shader::Shader(BufferLayout* layout, String vertexPath, String fragmentPath, bool path) : m_Layout(layout) {
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

		DX(HT_DXDEVICE->CreateVertexShader(vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize(), NULL, &m_VertexShader));

		ID3DBlob* fragmentShaderBlob = nullptr, *fragmentErrorBlob = nullptr;

		DX(D3DCompile(fragment, fSize, NULL, NULL, NULL, "main", "ps_5_0", flag, 0, &fragmentShaderBlob, &fragmentErrorBlob));
		if (fragmentErrorBlob) {
			HT_WARN("Fragment shader errors: \n%s", (const char*)fragmentErrorBlob->GetBufferPointer());
			fragmentErrorBlob->Release();
		}
		DX(HT_DXDEVICE->CreatePixelShader(fragmentShaderBlob->GetBufferPointer(), fragmentShaderBlob->GetBufferSize(), NULL, &m_FragmentShader));

		m_Layout->Init(vertexShaderBlob);
	
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
		HT_DXCONTEXT->VSSetShader(m_VertexShader, nullptr, 0);
		HT_DXCONTEXT->PSSetShader(m_FragmentShader, nullptr, 0);
		m_Layout->Start();
	}

} }

#endif