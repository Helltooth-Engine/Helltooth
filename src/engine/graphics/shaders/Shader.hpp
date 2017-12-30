#pragma once

#if defined(HT_OPENGL)
#include "platform/opengl/GL.hpp"
#elif defined(HT_DIRECTX)
#include "platform/directx/DX.hpp"
#endif

#include "graphics/Enums.hpp"
#include "graphics/buffers/UniformBuffer.hpp"
#include "graphics/buffers/VertexArray.hpp"

#include "utils/String.hpp"
#include "utils/FileUtils.hpp"
#include "utils/Vfs.hpp"

namespace ht { namespace graphics {

	class Shader {
	private:
		BufferLayout m_Layout;

		u32 m_Stride = 0;

#ifdef HT_OPENGL
		u32 m_Program;
		u32 m_VertexArray;
#elif defined(HT_DIRECTX)
		ID3D11VertexShader* m_VertexShader;
		ID3D11PixelShader* m_FragmentShader;
		ID3D11InputLayout* m_InputLayout;
#endif

	public:
		Shader(BufferLayout layout, utils::String vertexPath, utils::String fragmentPath, bool path = true);
		~Shader();

		void SetUniformBuffer(UniformBuffer* buffer);

		void Start();

		inline u32 GetStride() { return m_Stride; }

	};

} }