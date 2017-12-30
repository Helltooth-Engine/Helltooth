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
#endif
	public:
		VertexBuffer(const void* data, u32 size, BufferUsage usage);
		~VertexBuffer();

		void Bind(u32 stride = 0) const;
	};

} }