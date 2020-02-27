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