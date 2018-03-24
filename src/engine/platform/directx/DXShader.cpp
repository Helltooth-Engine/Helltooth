#ifdef HT_DIRECTX
#include "graphics/shaders/Shader.hpp"
#include "DX.hpp"

namespace ht { namespace graphics {
	using namespace core;
	using namespace utils;


	Shader::Shader(BufferLayout* layout, String vertexPath, String fragmentPath, int path) : m_Layout(layout) {
		UINT flag = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef HT_DEBUG
		flag |= D3DCOMPILE_DEBUG;
#endif
		char* vertex, *fragment;
		u32 vSize, fSize;
		if (path & ShaderLocationType::FROM_PATH != 0) {
			String vertexData = FileUtils::ReadFile(VFS::Resolve(vertexPath));
			String fragmentData = FileUtils::ReadFile(VFS::Resolve(fragmentPath));
			vSize = vertexData.GetSize() + 1;
			fSize = fragmentData.GetSize() + 1;

			
			if (path & ShaderLocationType::FROM_HTSL != 0) {
				htsl::Parser::Init();

				std::vector<std::string> result;
				result = htsl::Parser::Get()->Parse(vertexData.GetData());
				vSize = result[0].size();
				m_Layout = new ModelLayout(htsl::Parser::Get()->GetVertexInputLayout(), layout);
				modelLayout = true;
				vertex = new char[vSize + 1];
				memcpy(vertex, result[0].c_str(), vSize + 1);

				result = htsl::Parser::Get()->Parse(fragmentData.GetData());
				fSize = result[0].size();
				fragment = new char[fSize + 1];
				memcpy(fragment, result[0].c_str(), fSize + 1);

				htsl::Parser::End();
			}
			else {
				vertex = new char[vSize];
				memcpy(vertex, vertexData.GetData(), vSize);

				fragment = new char[fSize];
				memcpy(fragment, fragmentData.GetData(), fSize);
			}
		}
		else if (path & ShaderLocationType::FROM_MEMORY != 0) {
			vSize = vertexPath.GetSize() + 1;
			fSize = fragmentPath.GetSize() + 1;
			vertex = new char[vSize];
			fragment = new char[fSize];
			memcpy(vertex, vertexPath.GetData(), vSize);
			memcpy(fragment, fragmentPath.GetData(), fSize);
		}
		else {
			HT_ASSERT(true, "[Shader] ShaderLocationType Unknown!");
		}

		ID3DBlob* vertexShaderBlob = nullptr, *vertexErrorBlob = nullptr;
		D3DCompile(vertex, vSize, NULL, NULL, NULL, "main", "vs_5_0", flag, 0, &vertexShaderBlob, &vertexErrorBlob);
		if (vertexErrorBlob) {
			HT_WARN("Vertex shader errors: \n%s", static_cast<const char*>(vertexErrorBlob->GetBufferPointer()));
			vertexErrorBlob->Release();
		}

		DX(HT_DXDEVICE->CreateVertexShader(vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize(), NULL, &m_VertexShader));

		ID3DBlob* fragmentShaderBlob = nullptr, *fragmentErrorBlob = nullptr;

		D3DCompile(fragment, fSize, NULL, NULL, NULL, "main", "ps_5_0", flag, 0, &fragmentShaderBlob, &fragmentErrorBlob);
		if (fragmentErrorBlob) {
			HT_WARN("Fragment shader errors: \n%s", static_cast<const char*>(fragmentErrorBlob->GetBufferPointer()));
			fragmentErrorBlob->Release();
		}
		DX(HT_DXDEVICE->CreatePixelShader(fragmentShaderBlob->GetBufferPointer(), fragmentShaderBlob->GetBufferSize(), NULL, &m_FragmentShader));

		m_Layout->Init(vertexShaderBlob);
	
		vertexShaderBlob->Release();
		fragmentShaderBlob->Release();
		delete[] vertex;
		delete[] fragment;
	}

	Shader::~Shader() {
		m_VertexShader->Release();
		m_FragmentShader->Release();
		if (modelLayout)
			delete m_Layout;
	}

	void Shader::Start() {
		HT_DXCONTEXT->VSSetShader(m_VertexShader, nullptr, 0);
		HT_DXCONTEXT->PSSetShader(m_FragmentShader, nullptr, 0);
		m_Layout->Start();
	}

} }

#endif