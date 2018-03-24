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

		f32 sinXRot = sin(ToRadians(m_Rotation.x));
		f32 cosXRot = cos(ToRadians(m_Rotation.x));

		f32 sinYRot = sin(ToRadians(m_Rotation.y));
		f32 cosYRot = cos(ToRadians(m_Rotation.y));

		Vector3 movement = Vector3();

		if (m_Keys[HT_KEY_W]) {
			movement.x += sinYRot * cosXRot;
			movement.y += sinXRot;
			movement.z += cosYRot * cosXRot;
		}

		if (m_Keys[HT_KEY_S]) {
			movement.x += -sinYRot * cosXRot;
			movement.y += -sinXRot;
			movement.z += -cosYRot * cosXRot;
		}

		if (m_Keys[HT_KEY_A]) {
			movement.x += cosYRot;
			movement.z += -sinYRot;
		}

		if (m_Keys[HT_KEY_D]) {
			movement.x += -cosYRot;
			movement.z += sinYRot;
		}

		movement.Normalize();

		movement *= m_SpeedFactor * delta;

		m_Position += movement;

		m_ViewMatrix = Matrix4(1.0f);
		m_ViewMatrix.Rotate(Vector3(m_Rotation)).Translate(m_Position);
	}

} }