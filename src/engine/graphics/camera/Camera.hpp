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

#include "core/input/EventBufferer.hpp"
#include "core/input/EventDispatcher.hpp"

#include "maths/Matrix4.hpp"

namespace ht { namespace graphics {

	class Camera : public core::EventBufferer {
	protected:
		maths::Matrix4 m_ViewMatrix;
		maths::Vector3 m_Position;
		maths::Vector2 m_Rotation;

		Camera(const maths::Vector3& position) : EventBufferer("Camera"), m_Position(position) { core::EventDispatcher::Add(this); }
		Camera(f32 x, f32 y, f32 z) : EventBufferer("Camera"), m_Position(x, y, z) { core::EventDispatcher::Add(this); }

	public:
		~Camera() { core::EventDispatcher::Remove(this); }
		
		virtual void Update(f32 delta) = 0;

		inline maths::Matrix4 GetViewMatrix() { return m_ViewMatrix; }
		inline maths::Matrix4 GetSkyboxViewMatrix() { return maths::Matrix4(1.0f).Rotate(-m_Rotation.x, -m_Rotation.y, 0).Inverse(); }
		inline maths::Vector3 GetPosition() { return m_Position; }
	};

} }