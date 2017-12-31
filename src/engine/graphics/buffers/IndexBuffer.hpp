#pragma once

#if defined(HT_OPENGL)
#include "platform/opengl/GL.hpp"
#elif defined(HT_DIRECTX)
#include "platform/directx/DX.hpp"
#endif

#include "core/Internal.hpp"

#include "graphics/Enums.hpp"

namespace ht { namespace graphics {

	class IndexBuffer {
	private:
		u32 m_Count;
#if defined(HT_OPENGL)
		u32 m_IndexBuffer;
		GLenum m_Format;
#elif defined(HT_DIRECTX)
		ID3D11Buffer* m_IndexBuffer;
		DXGI_FORMAT m_Format;
#endif
	public:
		IndexBuffer(u32* indices, u32 indexCount, BufferUsage usage);
		IndexBuffer(u16* indices, u32 indexCount, BufferUsage usage);
		~IndexBuffer();

		void Bind();

#if defined(HT_OPENGL)
		inline GLenum GetFormat() { return m_Format; }
#elif defined(HT_DIRECTX)
		inline DXGI_FORMAT GetFormat() { return m_Format; }
#endif

		inline u32 GetCount() { return m_Count; }

	};

} }