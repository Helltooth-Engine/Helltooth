#pragma once

#if defined(HT_OPENGL)
#include "platform/opengl/GL.hpp"
#elif defined(HT_DIRECTX)
#include "platform/directx/DX.hpp"
#else
#error Platform not recognzied
#endif

#include "graphics/buffers/BufferLayout.hpp"

namespace ht { namespace graphics {

	class VertexArray {
	private:
		BufferLayout m_Layout;
#if defined(HT_OPENGL)
		u32 m_Array;
#elif defined(HT_DIRECTX)
		ID3D11InputLayout* m_InputLayout;
#endif
	public:
		VertexArray(BufferLayout layout);
		~VertexArray();

		void Bind();

#if defined(HT_DIRECTX)
		ID3D11InputLayout* GetInputLayout() { return m_InputLayout; }
#endif
	};

} }
