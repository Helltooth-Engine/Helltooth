#pragma once

#ifdef HT_OPENGL
#include "platform/opengl/GL.hpp"
#elif defined(HT_DIRECTX)
#include <d3d11.h>
#include "core/Window.hpp"
#endif

#include <unordered_map>

#include "graphics/buffers/BufferLayout.hpp"

#include "utils/String.hpp"

namespace ht { namespace graphics {

	class UniformBuffer {
	private:
		UniformBufferLayout m_Layout;
		std::vector<f32> m_Data;
		u32 m_Size;

#if defined(HT_OPENGL)
		u32 m_Buffer;
#elif defined(HT_DIRECTX)
		ID3D11Buffer* m_Buffer;
#else
#error Platform not recognized!
#endif
	public:
		UniformBuffer(UniformBufferLayout layout, BufferUsage usage = BufferUsage::DYNAMIC);
		~UniformBuffer();

		void Set(u32 index, void* data);
	};

} }