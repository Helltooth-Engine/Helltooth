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

#include <vector>

#include "entities/Entity.hpp"
#include "entities/ModelComponent.hpp"
#include "entities/SkyboxComponent.hpp"
#include "entities/TextureComponent.hpp"
#include "entities/TransformComponent.hpp"

#include "graphics/buffers/VertexBuffer.hpp"
#include "graphics/camera/Camera.hpp"
#include "graphics/shaders/Shader.hpp"

namespace ht { namespace graphics {

	struct Renderable {
		const entities::ModelComponent* model;
		std::vector<const entities::TransformComponent*> transforms;
	};

	struct InstanceData {
		maths::Matrix4 modelMatrix;
	};

	class Renderer {
	private:
		std::vector<Renderable>                         m_Renderables;
		std::vector<const entities::TextureComponent*>  m_TextureComponents;

		const entities::SkyboxComponent*                m_SkyboxComponent     = nullptr;
		entities::ModelComponent*                       m_Quad                = nullptr;

		maths::Matrix4                                  m_Projection;
		Shader*                                         m_Shader;
		Camera*                                         m_Camera              = nullptr;
		BufferLayout*                                   m_Layout              = nullptr;
		UniformBuffer*                                  m_Uniform             = nullptr;
		VertexBuffer*                                   m_InstanceData        = nullptr;


		Shader*                                         m_SkyboxShader;
		BufferLayout*                                   m_SkyboxLayout        = nullptr;
		UniformBuffer*                                  m_SkyboxUniform       = nullptr;

		uptr                                            m_InstaceDataSize     = 0;
		uptr                                            m_InstaceDataSizeLast = 0;
		bool                                            m_OwnShader           = false;

	public:
		Renderer(Camera* camera, maths::Matrix4 projection, Shader* shader = nullptr);
		~Renderer();

		void Submit(const entities::Entity& entity);

		void Render();

		void End() { m_Renderables.clear(); }

	private:
		void CreateSkyboxQuad();
	};

} }