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

#pragma once

#if defined(HT_OPENGL)
#include "platform/opengl/GL.hpp"
#elif defined(HT_DIRECTX)
#include <d3d11.h>
#endif // HT_OPENGL

#include "core/Internal.hpp"

#include "utils/Log.hpp"

namespace ht { namespace graphics {

	enum class BufferUsage {
#if defined(HT_OPENGL)
		STATIC   = GL_STATIC_DRAW,
		DYNAMIC  = GL_DYNAMIC_DRAW,
		STREAM   = GL_STREAM_DRAW,
#elif defined(HT_DIRECTX)
		STATIC   = D3D11_USAGE_IMMUTABLE,
		DYNAMIC  = D3D11_USAGE_DYNAMIC,
		STREAM   = D3D11_USAGE_DEFAULT,
#endif // HT_OPENGL
	};

	enum class DataType {
		VECTOR2,
		VECTOR3,
		VECTOR4,
		MATRIX4,
		TEXTURE_2D,
#if defined(HT_OPENGL)
		FLOAT           = GL_FLOAT,
		UNSIGNED_SHORT  = GL_UNSIGNED_SHORT,
		UNSIGNED_INT    = GL_UNSIGNED_INT,
		UNSIGNED_BYTE   = GL_UNSIGNED_BYTE,
#elif defined(HT_DIRECTX)
		FLOAT           = DXGI_FORMAT_R32_FLOAT,
		UNSIGNED_SHORT  = DXGI_FORMAT_R16_UINT,
		UNSIGNED_INT    = DXGI_FORMAT_R32_UINT,
		UNSIGNED_BYTE   = DXGI_FORMAT_R8_UINT,
#endif // HT_OPENGL
		
	};

	enum class ShaderType {
#if defined(HT_OPENGL)
		VERTEX    = GL_VERTEX_SHADER,
		FRAGMENT  = GL_FRAGMENT_SHADER,
#elif defined(HT_DIRECTX)
		VERTEX,
		FRAGMENT,
#endif // HT_OPENGL
		UNKOWN,
	};

	enum class TextureFormat {
		UNKNOWN = 0,
#if defined(HT_OPENGL)
		RGB   = GL_RGB,
		RGBA  = GL_RGBA,
		BGRA  = GL_BGRA,
#elif defined(HT_DIRECTX)
		RGB   = UNKNOWN, // no support
		RGBA  = DXGI_FORMAT_R8G8B8A8_UNORM,
		BGRA  = DXGI_FORMAT_B8G8R8A8_UNORM,
#endif // HT_OPENGL
	};

	enum class TextureType {
		UNKNOWN,
		TEXTURE_2D,
		TEXTURE_3D
	};

	enum class TextureCubeFace {
		RIGHT,
		LEFT,
		TOP,
		BOTTOM,
		FRONT,
		BACK
	};

	enum ShaderLocationType {
		FROM_MEMORY  = 0x0,
		FROM_PATH    = 0x1,
		FROM_HTSL    = 0xA
	};

	enum class BufferMapType {
#if defined(HT_OPENGL)
		READ_ONLY       = GL_READ_ONLY,
		WRITE_ONLY      = GL_WRITE_ONLY,
		READ_AND_WRITE  = GL_READ_WRITE,
#elif defined(HT_DIRECTX)
		READ_ONLY       = D3D11_MAP_READ,
		WRITE_ONLY      = D3D11_MAP_WRITE_DISCARD,
		READ_AND_WRITE  = D3D11_MAP_READ_WRITE,
#endif // HT_OPENGL
	};

	extern u32 DataTypeSize(DataType type);
	extern u32 TextureFormatSize(TextureFormat type);
	extern u32 GetSemanticIndex(DataType type);
	extern TextureFormat GetFormat(u32 bpp);
	extern TextureFormat GetBaseFormat(TextureFormat);

} }