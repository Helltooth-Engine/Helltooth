#pragma once
#if !(defined(HT_OPENGL) || defined(HT_DIRECTX))
#error "No Graphics API defined!"
#endif

#if !(defined(HT_WINDOWS) || defined(HT_LINUX))
#error "Platform not supported!"
#endif

#include "core/input/Event.hpp"
#include "core/input/EventBufferer.hpp"
#include "core/input/EventDispatcher.hpp"
#include "core/input/EventListener.hpp"
#include "core/input/Keys.hpp"
#include "core/Asset.hpp"
#include "core/Internal.hpp"
#include "core/Window.hpp"

#include "entities/Entity.hpp"
#include "entities/TransformComponent.hpp"

#include "graphics/buffers/BufferLayout.hpp"
#include "graphics/buffers/IndexBuffer.hpp"
#include "graphics/buffers/UniformBuffer.hpp"
#include "graphics/buffers/VertexBuffer.hpp"
#include "graphics/camera/Camera.hpp"
#include "graphics/camera/FPSCamera.hpp"
#include "graphics/shaders/Shader.hpp"
#include "graphics/Context.hpp"
#include "graphics/Enums.hpp"
#include "graphics/Texture.hpp"
#include "graphics/Texture2D.hpp"

#include "maths/Mathcommon.hpp"
#include "maths/Matrix4.hpp"
#include "maths/Vector2.hpp"
#include "maths/Vector3.hpp"
#include "maths/Vector4.hpp"

#include "utils/FileUtils.hpp"
#include "utils/Log.hpp"
#include "utils/String.hpp"
#include "utils/Timer.hpp"
#include "utils/Vfs.hpp"

namespace ht {
	class Application {
	protected:
		ht::core::Window *m_Window;
		u32 m_MaxUps;
		std::string m_Title;

	public:
		Application(const std::string& title, u32 width, u32 height, u32 maxUps = 60)
			: m_MaxUps(maxUps), m_Title(title) {
			m_Window = new ht::core::Window(title, width, height);
		}

		virtual void Init() = 0;
		virtual void Render() = 0;
		virtual void Update(float delta) = 0;
		virtual void Tick() = 0;

		void Start() {
			Init();

			f32 delta = 0.0f;
			f32 overallTime = 0.0f;
			f32 timeFactor = 1.0f / (f32)m_MaxUps;
			f32 timerDelta = 0.0f;

			u32 frames = 0;
			u32 updates = 0;

			ht::utils::Timer timer;
			while (!m_Window->ShouldClose()) {
				m_Window->Clear();

				if (delta >= timeFactor) {
					Update(delta);
					delta -= timeFactor;
					updates++;
				}

				Render();

				frames++;
				if (overallTime >= 1.0f) {
					m_Window->SetTitle(m_Title + " | Updates: " + std::to_string(updates) + " Frames: " + std::to_string(frames));
					updates = 0;
					frames = 0;
					delta = 0.0f;
					overallTime -= 1.0f;
				}
				m_Window->Update();
				timerDelta = timer.GetDelta();
				overallTime += timerDelta;
				delta += timerDelta;
			}
		}

	};

}
