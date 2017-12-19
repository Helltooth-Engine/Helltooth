#pragma once
#ifdef HT_OPENGL
#include "platform/opengl/GL.hpp"
#elif defined(HT_DIRECTX)
#include <d3d11.h>
#endif

namespace ht { namespace graphics {

	enum class BufferUsage {
#ifdef HT_OPENGL
		STATIC = GL_STATIC_DRAW,
		DYNAMIC = GL_DYNAMIC_DRAW
#elif defined(HT_DIRECTX)
		STATIC = D3D11_USAGE_DEFAULT,
		DYNAMIC = D3D11_USAGE_DYNAMIC
#endif
	};

	class VertexBuffer {
	private:
		unsigned int stride;
#ifdef HT_OPENGL
		unsigned int m_Buffer;
#elif defined(HT_DIRECTX)
		ID3D11Buffer* m_Buffer;
#endif
	public:
		VertexBuffer(const void* data, unsigned int size, unsigned int stride, BufferUsage usage);
		~VertexBuffer();

		void Bind() const;
	};

} }