﻿/*
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
#include "graphics/buffers/BufferLayout.hpp"

namespace ht { namespace graphics {

	BufferLayout::BufferLayout() { }
	BufferLayout::~BufferLayout() { m_InputLayout->Release(); }

	void BufferLayout::Init(void* shaderBlob) {
		ID3DBlob* shader = static_cast<ID3DBlob*>(shaderBlob);

		std::vector<D3D11_INPUT_ELEMENT_DESC> elementDescs;

		u32 lastBuffer = -1;

		for (u32 i = 0; i < m_Attributes.size(); i++) {
			D3D11_INPUT_ELEMENT_DESC current       = {};
			current.SemanticName                   = m_Attributes[i].semanticName.GetData();

			if (m_Attributes[i].type == DataType::MATRIX4) {
				for (int k = 0; k < 4; k++) {
					current.SemanticIndex          = k;
					current.Format                 = DXGI_FORMAT_R32G32B32A32_FLOAT;
					current.InputSlot              = m_Attributes[i].bufferId;
					current.InputSlotClass         = m_Attributes[i].instancing ? D3D11_INPUT_PER_INSTANCE_DATA : D3D11_INPUT_PER_VERTEX_DATA;
					current.InstanceDataStepRate   = m_Attributes[i].instancing ? 1 : 0;
					if (lastBuffer                != m_Attributes[i].bufferId) {
						lastBuffer                 = m_Attributes[i].bufferId;
						current.AlignedByteOffset  = 0;
					}
					else {
						current.AlignedByteOffset  = D3D11_APPEND_ALIGNED_ELEMENT;
					}
					elementDescs.push_back(current);
				}
			}
			else {
				current.SemanticIndex = 0;
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
						HT_ASSERT(false, "[BufferLayout] Attribute count not supported.");
					}
				}
				else {
					current.Format             = static_cast<DXGI_FORMAT>(m_Attributes[i].type);
				}

				current.InputSlot              = m_Attributes[i].bufferId;
				current.InputSlotClass         = m_Attributes[i].instancing ? D3D11_INPUT_PER_INSTANCE_DATA : D3D11_INPUT_PER_VERTEX_DATA;
				current.InstanceDataStepRate   = m_Attributes[i].instancing ? 1 : 0;
				if (lastBuffer                != m_Attributes[i].bufferId) {
					lastBuffer                 = m_Attributes[i].bufferId;
					current.AlignedByteOffset  = 0;
				}
				else {
					current.AlignedByteOffset  = D3D11_APPEND_ALIGNED_ELEMENT;
				}
				elementDescs.push_back(current);
			}
		}

		DX(HT_DXDEVICE->CreateInputLayout(&elementDescs[0], elementDescs.size(), shader->GetBufferPointer(), shader->GetBufferSize(), &m_InputLayout));
	}

	void BufferLayout::Bind(const VertexBuffer** buffers) {
		HT_DXCONTEXT->IASetInputLayout(m_InputLayout);
		static u32 offset = 0;
		for (u32 i = 0; i <= m_BuffersCount; i++) {
			ID3D11Buffer* currentBuffer = buffers[i]->GetBuffer();
			
			HT_DXCONTEXT->IASetVertexBuffers(i, 1, &currentBuffer, &m_Stride[i], &offset);
		}
		

	}

} }

#endif // HT_DIRECTX