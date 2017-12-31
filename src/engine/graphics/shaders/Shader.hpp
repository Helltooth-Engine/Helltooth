#pragma once

#if defined(HT_OPENGL)
#include "platform/opengl/GL.hpp"
#elif defined(HT_DIRECTX)
#include "platform/directx/DX.hpp"
#endif

#include "graphics/Enums.hpp"

#include "graphics/buffers/BufferLayout.hpp"
#include "graphics/buffers/UniformBuffer.hpp"

#include "utils/String.hpp"
#include "utils/FileUtils.hpp"
#include "utils/Vfs.hpp"

namespace ht { namespace graphics {

	class Shader {
	private:
		BufferLayout* m_Layout;

#ifdef HT_OPENGL
		u32 m_Program;
		u32 m_VertexArray;
#elif defined(HT_DIRECTX)
		ID3D11VertexShader* m_VertexShader;
		ID3D11PixelShader* m_FragmentShader;
#endif

	public:
		Shader(BufferLayout* layout, utils::String vertexPath, utils::String fragmentPath, bool path = true);
		~Shader();

		void Start();

		inline u32 GetStride() { 
#ifdef HT_DIRECTX
			return m_Layout->GetStride();
#else
			return 0;
#endif
		}

	};

} }