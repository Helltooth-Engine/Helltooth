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