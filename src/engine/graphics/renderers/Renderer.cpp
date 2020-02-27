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

#include "Renderer.hpp"

namespace ht { namespace graphics {
	using namespace maths;
	using namespace entities;

	Renderer::Renderer(Camera* camera, Matrix4 projection, Shader* shader)
		: m_Projection(projection), m_Camera(camera) {
		if (shader == nullptr) {
			const char* vertexShader = 
				#include "graphics/shaders/default/RendererShaderVertex.htsl"
				;
			const char* fragmentShader =
				#include "graphics/shaders/default/RendererShaderFragment.htsl"
				;

			m_Layout = new BufferLayout();
			m_Layout->AddLayout<float>("POSITION",       3, false, false, 0);
			m_Layout->AddLayout<float>("UV",             2, false, false, 0);
			m_Layout->AddLayout<float>("NORMALS",        3, false, false, 0);
			m_Layout->AddLayout<Matrix4>("MODELMATRIX",  1, false, true,  1);

			m_Shader = new Shader(m_Layout, vertexShader, fragmentShader, ShaderLocationType::FROM_HTSL | ShaderLocationType::FROM_MEMORY);
#if defined(HT_OPENGL)

			s32 ids[] = {
				 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 
				16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31 
			};
			
			m_Shader->Start();
			m_Shader->SetSamplers(ids, 32);
#endif // HT_OPENGL
			m_OwnShader = true;
		}
		else
			m_Shader = shader;

		const char* vertexShader =
			#include "graphics/shaders/default/RendererSkyboxVertex.htsl"
			;
		const char* fragmentShader =
			#include "graphics/shaders/default/RendererSkyboxFragment.htsl"
			;

		m_SkyboxLayout = new BufferLayout();
		m_SkyboxLayout->AddLayout<float>("POSITION", 3, false, false, 0);

		m_SkyboxShader = new Shader(m_SkyboxLayout, vertexShader, fragmentShader, ShaderLocationType::FROM_HTSL | ShaderLocationType::FROM_MEMORY);

#if defined(HT_OPENGL)
		m_SkyboxShader->Start();
		m_SkyboxShader->SetSampler("textureCube", 0);
#endif // HT_OPENGL

		UniformBufferLayout uniformLayout = UniformBufferLayout(ShaderType::VERTEX);
		uniformLayout.AddUniform<Matrix4>();
		uniformLayout.AddUniform<Matrix4>();

		m_Uniform = new UniformBuffer(uniformLayout);
		m_Uniform->Set(0, &m_Projection[0]);

		UniformBufferLayout skyboxUniformLayout = UniformBufferLayout(ShaderType::VERTEX);
		skyboxUniformLayout.AddUniform<Matrix4>();

		m_SkyboxUniform = new UniformBuffer(skyboxUniformLayout);
	}

	Renderer::~Renderer() {
		if (m_Layout) delete m_Layout;
		if (m_OwnShader) delete m_Shader;
		delete m_Uniform;
		delete m_SkyboxLayout, m_SkyboxShader, m_SkyboxUniform;
	}

	void Renderer::Submit(const entities::Entity& entity) {
		
		const ModelComponent* model = entity.GetComponent<ModelComponent>();
		// Entity doesn't have a model component, test to see if it has a skybox component
		if (!model) {
			const SkyboxComponent* skybox = entity.GetComponent<SkyboxComponent>();			
			
			m_SkyboxComponent = skybox;
			HT_ASSERT(skybox, "[Renderer] Entities must have a Model or a Skybox");
			if (m_Quad == nullptr)
				CreateSkyboxQuad();
			return;
		}

		const TransformComponent* transform = entity.GetComponent<TransformComponent>();
		
		bool foundModel = false;
		for (size_t i = 0; i < m_Renderables.size(); i++) {
			if (model == m_Renderables[i].model) {
				m_Renderables[i].transforms.push_back(transform);
				if (m_InstaceDataSize < m_Renderables[i].transforms.size() - 1)
					m_InstaceDataSize = m_Renderables[i].transforms.size() - 1;
				foundModel = true;
				break;
			}
		}
		if (!foundModel) {
			m_Renderables.push_back({ model });
			m_Renderables[m_Renderables.size() - 1].transforms.push_back(transform);
		}
		bool foundTexture = false;
		const TextureComponent* texture = entity.GetComponent<TextureComponent>();
		if (texture) {
			for (u32 i = 0; i < m_TextureComponents.size(); i++)
				if (m_TextureComponents[i] == texture) {
					foundTexture = true;
					break;
				}
			if (!foundTexture)
				m_TextureComponents.push_back(texture);
		}
		if (m_InstaceDataSize < 1)
			m_InstaceDataSize = 1;
	}
	
	void Renderer::Render() {
		// First render the skybox
		if (m_SkyboxComponent) {
			m_SkyboxShader->Start();
			Matrix4 inverseViewMatrix = m_Camera->GetSkyboxViewMatrix();
			m_SkyboxUniform->Set(0, &inverseViewMatrix[0]);
			m_SkyboxUniform->Bind();

			m_SkyboxComponent->GetTexture()->Bind(0);

			const VertexBuffer* buffers[] = { m_Quad->GetVertexBuffer() };
			m_SkyboxShader->BindLayout(buffers);
			m_Quad->GetIndexBuffer()->Bind();
#if defined(HT_OPENGL)
			GL(glDrawElements(GL_TRIANGLES, m_Quad->GetIndexBuffer()->GetCount(), m_Quad->GetIndexBuffer()->GetFormat(), nullptr));
#elif defined(HT_DIRECTX)
			HT_DXCONTEXT->DrawIndexed(m_Quad->GetIndexBuffer()->GetCount(), 0, 0);
#endif // HT_OPENGL
		}
		for (u32 i = 0; i < m_TextureComponents.size(); i++)
			m_TextureComponents[i]->GetTexture()->Bind(i);

		m_Shader->Start();
		m_Uniform->Set(1, &m_Camera->GetViewMatrix()[0]);
		m_Uniform->Bind();
		if (m_InstaceDataSize != m_InstaceDataSizeLast) {
			if (m_InstanceData)
				delete m_InstanceData;
			m_InstanceData = new VertexBuffer(0, static_cast<u32>(m_InstaceDataSize * sizeof(InstanceData)), BufferUsage::DYNAMIC);
			m_InstaceDataSizeLast = m_InstaceDataSize;
		}
		for (Renderable& renderable : m_Renderables) {
			InstanceData* data = static_cast<InstanceData*>(m_InstanceData->Map(BufferMapType::WRITE_ONLY));
			for (u32 i = 0; i < renderable.transforms.size(); i++) {
				memcpy(data, &renderable.transforms[i]->GetModelMatrix()[0], sizeof(Matrix4));
				data++;
			}
			m_InstanceData->Unmap();
			m_InstanceData->Bind(m_Shader->GetStride());
			const VertexBuffer* buffers[] = { renderable.model->GetVertexBuffer(), m_InstanceData };

			m_Shader->BindLayout(buffers);
			renderable.model->GetIndexBuffer()->Bind();
#if defined(HT_OPENGL)
			GL(glDrawElementsInstanced(GL_TRIANGLES, renderable.model->GetIndexBuffer()->GetCount(), renderable.model->GetIndexBuffer()->GetFormat(), nullptr, static_cast<GLsizei>(renderable.transforms.size())));
#elif defined(HT_DIRECTX)
			HT_DXCONTEXT->DrawIndexedInstanced(renderable.model->GetIndexBuffer()->GetCount(), m_InstaceDataSize, 0, 0, 0);
#endif // HT_OPENGL

		}
	}

	void Renderer::CreateSkyboxQuad() {
		f32 vertices[] = {
			-1.0f,  1.0f, 0.0f,
			-1.0f, -1.0f, 0.0f,
			 1.0f, -1.0f, 0.0f,
			 1.0f,  1.0f, 0.0f
		};

		// if it doesn't work, it's clockwise
		u32 indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		m_Quad = new ModelComponent(vertices, sizeof(vertices));
		m_Quad->SetIndices(indices, sizeof(indices));
	}

} }