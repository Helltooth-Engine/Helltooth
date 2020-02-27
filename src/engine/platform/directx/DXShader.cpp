/*
 * Copyright (c) 2020 Rareș-Nicolaie Ciorbă
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#ifdef HT_DIRECTX
#include "DX.hpp"
#include "graphics/shaders/Shader.hpp"

namespace ht { namespace graphics {
	using namespace core;
	using namespace utils;

	Shader::Shader(BufferLayout* layout, const String& vertexPath, const String& fragmentPath, int path) 
		: m_Layout(layout) {
		UINT flag = D3DCOMPILE_ENABLE_STRICTNESS;

#if defined(HT_DEBUG)
		flag |= D3DCOMPILE_DEBUG;
#endif // HT_DEBUG

		char* vertex, *fragment;
		u32 vSize, fSize;
		if ((path & ShaderLocationType::FROM_PATH) != 0) {
			String vertexData   = FileUtils::ReadFile(VFS::Resolve(vertexPath));
			String fragmentData = FileUtils::ReadFile(VFS::Resolve(fragmentPath));
			vSize               = vertexData.GetSize()   + 1;
			fSize               = fragmentData.GetSize() + 1;
			
			if ((path & ShaderLocationType::FROM_HTSL) != 0) {
				htsl::Parser::Init();

				std::vector<std::string> result;
				result = htsl::Parser::Get()->Parse(vertexData.GetData());
				vSize = result[0].size();
				m_Layout->SetSemanticNames(htsl::Parser::Get()->GetVertexInputLayout());
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
		else {
			String vertData = vertexPath;
			String fragData = fragmentPath;
			if ((path & ShaderLocationType::FROM_HTSL) != 0) {
				htsl::Parser::Init();
				std::vector<std::string> result;
				result = htsl::Parser::Get()->Parse(vertexPath.GetData());
				m_Layout->SetSemanticNames(htsl::Parser::Get()->GetVertexInputLayout());
				modelLayout = true;
				vertData = result[0];

				result = htsl::Parser::Get()->Parse(fragmentPath.GetData());
				fragData = result[0];

				htsl::Parser::End();
			}
			vSize = vertData.GetSize() + 1;
			fSize = fragData.GetSize() + 1;
			vertex = new char[vSize];
			fragment = new char[fSize];
			memcpy(vertex, vertData.GetData(), vSize);
			memcpy(fragment, fragData.GetData(), fSize);
		}

		ID3DBlob* vertexShaderBlob = nullptr, *vertexErrorBlob = nullptr;
		D3DCompile(vertex, vSize, NULL, NULL, NULL, "main", "vs_5_0", flag, 0, &vertexShaderBlob, &vertexErrorBlob);
		if (vertexErrorBlob) {
			HT_MSG("Vertex shader code: \n%s", vertex);
			HT_WARN("Vertex shader errors: \n%s", static_cast<const char*>(vertexErrorBlob->GetBufferPointer()));
			vertexErrorBlob->Release();
		}

		DX(HT_DXDEVICE->CreateVertexShader(vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize(), NULL, &m_VertexShader));

		ID3DBlob* fragmentShaderBlob = nullptr, *fragmentErrorBlob = nullptr;

		D3DCompile(fragment, fSize, NULL, NULL, NULL, "main", "ps_5_0", flag, 0, &fragmentShaderBlob, &fragmentErrorBlob);
		if (fragmentErrorBlob) {
			HT_MSG("Fragment shader code: \n%s", fragment);
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

		if (modelLayout) delete m_Layout;
	}

	void Shader::Start() {
		HT_DXCONTEXT->VSSetShader(m_VertexShader, nullptr, 0);
		HT_DXCONTEXT->PSSetShader(m_FragmentShader, nullptr, 0);
	}

} }

#endif // HT_DIRECTX