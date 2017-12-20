#pragma once

#ifdef HT_OPENGL
#include "platform/opengl/GL.hpp"
#elif defined(HT_DIRECTX)
#include <d3d11.h>
#endif

#include <vector>

#include "core/Internal.hpp"

#include "graphics/Enums.hpp"

#include "utils/Log.hpp"

namespace ht { namespace graphics {

	struct BufferAttribute {
		DataType type;
		u16 count;
		u16 stride;
		bool normalized;
	};

	struct BufferLayout {
		std::vector<BufferAttribute> attributes;

		template<typename T>
		void AddLayout(u16 count, u16 stride, bool normalized) {
			HT_ASSERT(true, "[BufferLayout] Data type not recognized.");
		}

		template<>
		void AddLayout<float>(u16 count, u16 stride, bool normalized) {
			attributes.push_back({ DataType::FLOAT, count, stride, normalized });
		}

		template<>
		void AddLayout<unsigned short>(u16 count, u16 stride, bool normalized) {
			attributes.push_back({ DataType::UNSIGNED_SHORT, count, stride, normalized });
		}

		template<>
		void AddLayout<unsigned int>(u16 count, u16 stride, bool normalized) {
			attributes.push_back({ DataType::UNSIGNED_INT, count, stride, normalized });
		}

	};

	class VertexBuffer {
	private:
		BufferLayout m_Layout;
#ifdef HT_OPENGL
		u32 m_Buffer;
#elif defined(HT_DIRECTX)
		ID3D11Buffer* m_Buffer;
		u32 m_Stride = 0;
		u32 m_Offset = 0;
#endif
	public:
		VertexBuffer(const void* data, u32 size, BufferLayout layout, BufferUsage usage);
		~VertexBuffer();

		void Bind() const;

		const BufferLayout& GetLayout() { return m_Layout; }
	};

} }