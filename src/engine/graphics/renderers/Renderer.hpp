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

		u32                                             m_InstaceDataSize     = 0;
		u32                                             m_InstaceDataSizeLast = 0;
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