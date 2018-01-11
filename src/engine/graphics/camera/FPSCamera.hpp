#pragma once

#include "Camera.hpp"

namespace ht { namespace graphics {

	class FPSCamera : public Camera {
	private:
		f32 m_SpeedFactor = 10; // 10 units / second 
		f32 m_YawSensitivity = 0.2f; // degrees / second
		f32 m_PitchSensitivty = 0.2f; // degres / second
		
		maths::Vector2 m_MouseLast;
	public:
		FPSCamera(const maths::Vector3& position);
		FPSCamera(f32 x, f32 y, f32 z);

		void Update(f32 delta) override;

	};

} }