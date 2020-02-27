#pragma once

#include <string.h>
#include <math.h>

#include "core/Internal.hpp"

#include "maths/Mathcommon.hpp"
#include "maths/Vector2.hpp"
#include "maths/Vector3.hpp"
#include "maths/Vector4.hpp"

namespace ht { namespace maths {

	class Matrix4 {
	private:
		union {
			f32 elements[4 * 4];
			Vector4 columns[4];
		};

		void LoadRows(__m128* xmm) const;
		void LoadColumns(__m128* xmm) const;

	public:
		Matrix4(f32 diagonal = 0.0f);

		static Matrix4 CreatePerspective(f32 fieldOfView, f32 nearPlane, f32 farPlane, f32 aspectRatio);
		static Matrix4 CreateOrthographic(f32 left, f32 right, f32 top, f32 bottom, f32 near, f32 far);

		Matrix4& Translate(f32 x, f32 y, f32 z);
		Matrix4& Translate(const Vector3& translation);

		Matrix4& Scale(f32 x, f32 y, f32 z);
		Matrix4& Scale(const Vector3& scale);

		Matrix4& Rotate(f32 x, f32 y, f32 z);
		Matrix4& Rotate(const Vector3& rotation);

		Matrix4& Transpose();

		Matrix4 Inverse();

		friend Matrix4 operator*(const Matrix4& left, const Matrix4& right);
		friend Vector4 operator*(const Matrix4& left, const Vector4& right);
		friend Vector3 operator*(const Matrix4& left, const Vector3& right);
		friend Vector2 operator*(const Matrix4& left, const Vector2& right);

		Matrix4 operator*=(const Matrix4& other);
		Vector4 operator*=(const Vector4& other);
		Vector3 operator*=(const Vector3& other);
		Vector2 operator*=(const Vector2& other);

		inline f32& operator[](unsigned int i) { return elements[i]; }
	};

} }