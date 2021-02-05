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
#include "entities/ModelComponent.hpp"
#include "entities/TextureComponent.hpp"
#include "entities/TransformComponent.hpp"

#include "graphics/buffers/BufferLayout.hpp"
#include "graphics/buffers/IndexBuffer.hpp"
#include "graphics/buffers/UniformBuffer.hpp"
#include "graphics/buffers/VertexBuffer.hpp"
#include "graphics/camera/Camera.hpp"
#include "graphics/camera/FPSCamera.hpp"
#include "graphics/renderers/Renderer.hpp"
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
		core::Window *m_Window;
		u32 m_MaxUps;
		std::string m_Title;

	public:
		Application(const std::string& title, u32 width, u32 height, u32 maxUps = 60)
			: m_MaxUps(maxUps), m_Title(title) {
			m_Window = new core::Window(title, width, height);
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

			utils::Timer timer;
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
