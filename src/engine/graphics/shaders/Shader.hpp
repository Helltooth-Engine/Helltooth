/*
 * Copyright (c) 2020 Rareș-Nicolaie Ciorbă
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

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
		inline void SetSamplers(s32* array, u32 size) { 
			GL(int loc = glGetUniformLocation(m_Program, "textures"));
			GL(glUniform1iv(loc, size, array)); 
		}
		
		inline void SetSampler(const utils::String& name, u32 value) {
			GL(int loc = glGetUniformLocation(m_Program, name.GetData()));
			GL(glUniform1i(loc, value));
		}
#elif defined(HT_DIRECTX)
		void SetSamplers(s32* array, u32 size) { }
#endif // HT_OPENGL

		inline void BindLayout(const VertexBuffer** buffers = nullptr) { m_Layout->Bind(buffers); }
		
	};

} }