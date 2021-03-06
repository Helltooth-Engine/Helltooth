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
#include "graphics/TextureCube.hpp"

namespace ht { namespace graphics {

	void TextureCube::SetSamplerState() {
		D3D11_SAMPLER_DESC samplerDesc = {};

		samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.MaxAnisotropy = 1;
		samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
		samplerDesc.MipLODBias = 0.4f;

		HT_DXDEVICE->CreateSamplerState(&samplerDesc, &m_SamplerState);
	}
	
	TextureCube::TextureCube(u32 width, u32 height, TextureFormat format)
		: Texture(width, height, TextureType::TEXTURE_3D, format) {
		SetSamplerState();

		D3D11_TEXTURE2D_DESC textureDesc = {};

		textureDesc.Width               = width;
		textureDesc.Height              = height;
		textureDesc.MipLevels           = 0;
		textureDesc.ArraySize           = 6;
		textureDesc.Format              = static_cast<DXGI_FORMAT>(GetBaseFormat(format));
		textureDesc.BindFlags           = D3D11_BIND_SHADER_RESOURCE;
		textureDesc.CPUAccessFlags      = 0;
		textureDesc.Usage               = D3D11_USAGE_DYNAMIC;
		textureDesc.MiscFlags           = D3D11_RESOURCE_MISC_TEXTURECUBE;
		textureDesc.SampleDesc.Count    = 1;
		textureDesc.SampleDesc.Quality  = 0;

		DX(HT_DXDEVICE->CreateTexture2D(&textureDesc, NULL, &m_Texture));

		D3D11_SHADER_RESOURCE_VIEW_DESC viewDesc = {};

		viewDesc.Format                       = textureDesc.Format;
		viewDesc.ViewDimension                = D3D11_SRV_DIMENSION_TEXTURECUBE;
		viewDesc.TextureCube.MipLevels        = 1;
		viewDesc.TextureCube.MostDetailedMip  = 0;

		DX(HT_DXDEVICE->CreateShaderResourceView(m_Texture, &viewDesc, &m_ResourceView));
	}

	TextureCube::TextureCube(byte** pixels, u32 width, u32 height, TextureFormat format) 
		: Texture(width, height, TextureType::TEXTURE_3D, format) {
		HT_ASSERT(pixels != nullptr, "[TextureCube] Pixel array can not be nullptr.");
		
		SetSamplerState();

		D3D11_TEXTURE2D_DESC textureDesc = {};
		
		textureDesc.Width               = width;
		textureDesc.Height              = height;
		textureDesc.MipLevels           = 1;
		textureDesc.ArraySize           = 6;
		textureDesc.Format              = static_cast<DXGI_FORMAT>(GetBaseFormat(format));
		textureDesc.BindFlags           = D3D11_BIND_SHADER_RESOURCE;
		textureDesc.CPUAccessFlags      = 0;
		textureDesc.Usage               = D3D11_USAGE_DEFAULT;
		textureDesc.MiscFlags           = D3D11_RESOURCE_MISC_TEXTURECUBE;
		textureDesc.SampleDesc.Count    = 1;
		textureDesc.SampleDesc.Quality  = 0;

		D3D11_SUBRESOURCE_DATA r[6] = {};
		
		for (u32 i = 0; i < 6; i++) {
			r[i].pSysMem = pixels[i];
			r[i].SysMemPitch = width * TextureFormatSize(format);
		}

		DX(HT_DXDEVICE->CreateTexture2D(&textureDesc, r, &m_Texture));

		D3D11_SHADER_RESOURCE_VIEW_DESC viewDesc = {};

		viewDesc.Format                       = textureDesc.Format;
		viewDesc.ViewDimension                = D3D11_SRV_DIMENSION_TEXTURECUBE;
		viewDesc.TextureCube.MipLevels        = 1;
		viewDesc.TextureCube.MostDetailedMip  = 0;
		
		DX(HT_DXDEVICE->CreateShaderResourceView(m_Texture, &viewDesc, &m_ResourceView));
	}

	TextureCube::~TextureCube() {
		m_Texture->Release();
	}

	void TextureCube::SetPixels(byte** pixels) {
		// TODO: make sure this is actually a thing
		HT_DXCONTEXT->UpdateSubresource(m_Texture, 0, NULL, pixels, m_Width * TextureFormatSize(m_Format) * 6, 0);

	}

	void TextureCube::Bind(u32 slot) const {
		HT_DXCONTEXT->PSSetShaderResources(slot, 1, &m_ResourceView);
		HT_DXCONTEXT->PSSetSamplers(slot, 1, &m_SamplerState);
	}

} }

#endif // HT_DIRECTX