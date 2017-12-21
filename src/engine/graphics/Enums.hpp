#pragma once

#if defined(HT_OPENGL)
#include "platform/opengl/GL.hpp"
#elif defined(HT_DIRECTX)
#include <d3d11.h>
#else
#error Platform not recognized!
#endif

#include "core/Internal.hpp"

#include "utils/Log.hpp"

namespace ht { namespace graphics {

	enum class BufferUsage {
#ifdef HT_OPENGL
		STATIC = GL_STATIC_DRAW,
		DYNAMIC = GL_DYNAMIC_DRAW
#elif defined(HT_DIRECTX)
		STATIC = D3D11_USAGE_DEFAULT,
		DYNAMIC = D3D11_USAGE_DYNAMIC
#else
#error Platform not recognized!
#endif
	};

	enum class DataType {
#ifdef HT_OPENGL
		FLOAT = GL_FLOAT,
		UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
		UNSIGNED_INT = GL_UNSIGNED_INT,
		UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
#elif defined(HT_DIRECTX)
		FLOAT = DXGI_FORMAT_R32_FLOAT,
		UNSIGNED_SHORT = DXGI_FORMAT_R16_UINT,
		UNSIGNED_INT = DXGI_FORMAT_R32_UINT,
		UNSIGNED_BYTE = DXGI_FORMAT_R8_UINT,
#else
#error Platform not recognized!
#endif
		VECTOR2,
		VECTOR3,
		VECTOR4,
		MATRIX4
	};

	inline extern u32 DataTypeSize(DataType type);

} }