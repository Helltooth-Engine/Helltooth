#pragma once

#if defined(HT_OPENGL)
#include "platform/opengl/GL.hpp"
#elif defined(HT_DIRECTX)
#include "platform/directx/DX.hpp"
#endif // HT_OPENGL

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
#endif // HT_OPENGL

	public:
		IndexBuffer(const u32* indices, u32 indexCount, BufferUsage usage);
		IndexBuffer(const u16* indices, u32 indexCount, BufferUsage usage);
		~IndexBuffer();

		void Bind() const;

#if defined(HT_OPENGL)
		inline GLenum GetFormat() const { return m_Format; }
#elif defined(HT_DIRECTX)
		inline DXGI_FORMAT GetFormat() const { return m_Format; }
#endif // HT_OPENGL

		inline u32 GetCount() const { return m_Count; }

	};

} }