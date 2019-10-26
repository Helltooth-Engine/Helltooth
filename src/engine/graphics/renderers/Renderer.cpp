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

		UniformBufferLayout m_UniformLayout = UniformBufferLayout(ShaderType::VERTEX);
		m_UniformLayout.AddUniform<Matrix4>();
		m_UniformLayout.AddUniform<Matrix4>();

		m_Uniform = new UniformBuffer(m_UniformLayout);
		m_Uniform->Set(0, &m_Projection[0]);
	}

	Renderer::~Renderer() {
		if (m_Layout) delete m_Layout;
		if (m_OwnShader) delete m_Shader;
		delete m_Uniform;
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
		}

		const TransformComponent* transform = entity.GetComponent<TransformComponent>();
		
		for (size_t i = 0; i < m_Renderables.size(); i++) {
			if (model == m_Renderables[i].model) {
				m_Renderables[i].transforms.push_back(transform);
				if (m_InstaceDataSize < m_Renderables[i].transforms.size() - 1)
					m_InstaceDataSize = m_Renderables[i].transforms.size() - 1;
				return;
			}
		}
		m_Renderables.push_back({ model });
		m_Renderables[m_Renderables.size() - 1].transforms.push_back(transform);
		if (m_InstaceDataSize < 1)
			m_InstaceDataSize = 1;
	}
	
	void Renderer::Render() {
		m_Shader->Start();
		m_Uniform->Set(1, &m_Camera->GetViewMatrix()[0]);
		m_Uniform->Bind();
		if (m_InstaceDataSize != m_InstaceDataSizeLast) {
			if (m_InstanceData)
				delete m_InstanceData;
			m_InstanceData = new VertexBuffer(0, m_InstaceDataSize * sizeof(InstanceData), BufferUsage::DYNAMIC);
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
			GL(glDrawElementsInstanced(GL_TRIANGLES, renderable.model->GetIndexBuffer()->GetCount(), renderable.model->GetIndexBuffer()->GetFormat(), nullptr, renderable.transforms.size()));
#elif defined(HT_DIRECTX)
			HT_DXCONTEXT->DrawIndexedInstanced(renderable.model->GetIndexBuffer()->GetCount(), m_InstaceDataSize, 0, 0, 0);
#endif // HT_OPENGL

		}
	}

	void Renderer::CreateSkyboxQuad() {
		f32 vertices[] = {
			-1.0f,  1.0f,
			-1.0f, -1.0f,
			 1.0f, -1.0f,
			 1.0f,  1.0f
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