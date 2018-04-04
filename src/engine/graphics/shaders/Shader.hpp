#pragma once

#if defined(HT_OPENGL)
#include "platform/opengl/GL.hpp"
#elif defined(HT_DIRECTX)
#include "platform/directx/DX.hpp"
#endif // HT_OPENGL

#include <Parser.hpp>

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
		bool modelLayout = false;

#ifdef HT_OPENGL
		u32 m_Program;
		u32 m_VertexArray;
#elif defined(HT_DIRECTX)
		ID3D11VertexShader* m_VertexShader;
		ID3D11PixelShader* m_FragmentShader;
#endif // HT_OPENGL

	public:
		Shader(BufferLayout* layout, const utils::String& vertexPath, const utils::String& fragmentPath, int path = ShaderLocationType::FROM_PATH);
		~Shader();

		void Start();

		inline u32 GetStride() { 
#ifdef HT_DIRECTX
			return m_Layout->GetStride();
#else
			return 0;
#endif // HT_DIRECTX
		}

#if defined(HT_OPENGL)
		inline void SetSamplers(s32* array, u32 size) { glUniform1iv(glGetUniformLocation(m_Program, "samplers"), size, array); }
#elif defined(HT_DIRECTX)
		void SetSamplers(s32* array, u32 size);
#endif // HT_OPENGL

		inline void BindLayout() { m_Layout->Bind(); }
		
	};

} }