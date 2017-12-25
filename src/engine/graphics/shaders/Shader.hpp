#pragma once

#ifdef HT_OPENGL
#include "platform/opengl/GL.hpp"
#elif defined(HT_DIRECTX)
#include <d3d11.h>
#include "core/Window.hpp"
#endif

#include "graphics/Enums.hpp"
#include "graphics/buffers/UniformBuffer.hpp"
#include "graphics/buffers/VertexBuffer.hpp"

#include "utils/String.hpp"
#include "utils/FileUtils.hpp"
#include "utils/Vfs.hpp"

namespace ht { namespace graphics {

	class Shader {
	private:
#ifdef HT_OPENGL
		u32 m_Program;
#elif defined(HT_DIRECTX)

#endif

	public:
		Shader(utils::String vertexPath, utils::String fragmentPath, bool path = true);
		~Shader();

		void SetUniformBuffer(UniformBuffer* buffer);
		void SetBufferLayout(VertexBuffer* buffer);

		void Start();

	};

} }