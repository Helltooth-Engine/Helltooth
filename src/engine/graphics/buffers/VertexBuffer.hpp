#pragma once

#if defined(HT_OPENGL)
#include "platform/opengl/GL.hpp"
#elif defined(HT_DIRECTX)
#include "platform/directx/DX.hpp"
#else
#error Platform not recognzied
#endif

#include <vector>

#include "core/Internal.hpp"

#include "graphics/Enums.hpp"

#include "utils/Log.hpp"

namespace ht { namespace graphics {

	class VertexBuffer {
	private:
#ifdef HT_OPENGL
		u32 m_Buffer;
#elif defined(HT_DIRECTX)
		ID3D11Buffer* m_Buffer;
		
		u32 m_Stride = 0;
		u32 m_Offset = 0;
#endif
	public:
		VertexBuffer(const void* data, u32 size, BufferUsage usage);
		~VertexBuffer();

		void Bind() const;
	};

} }