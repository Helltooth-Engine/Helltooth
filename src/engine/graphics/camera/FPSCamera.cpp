#include "FPSCamera.hpp"


namespace ht { namespace graphics {
	using namespace maths;

	FPSCamera::FPSCamera(const Vector3& position)
		: Camera(position) { }

	FPSCamera::FPSCamera(f32 x, f32 y, f32 z)
		: Camera(x, y, z) { }

	void FPSCamera::Update(f32 delta) {
		if (m_MouseKeys[HT_MOUSE_RBUTTON]) {
			f32 hMovement = (m_MouseX - m_MouseLast.x) * m_YawSensitivity;
			f32 vMovement = (m_MouseY - m_MouseLast.y) * m_PitchSensitivty;

			m_Rotation.x += vMovement;
			m_Rotation.y -= hMovement;

			if (m_Rotation.x < -90) {
				m_Rotation.x = -90;
			}
			if (m_Rotation.x > 90) {
				m_Rotation.x = 90;
			}

			if (m_Rotation.y < 0) {
				m_Rotation.y += 360;
			}
			if (m_Rotation.y > 360) {
				m_Rotation.y += -360;
			}

		}

		m_MouseLast = Vector2(m_MouseX, m_MouseY);


		//if (m_Keys[HT_KEY_W]) {
		//	m_Position.x += m_SpeedFactor * delta;
		//}

		m_ViewMatrix = Matrix4(1.0f);
		m_ViewMatrix.Rotate(Vector3(m_Rotation));
	}

} }