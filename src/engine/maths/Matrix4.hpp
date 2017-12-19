#pragma once

#include <string.h>

#include "Vector2.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"

#include "Mathcommon.hpp"

namespace ht { namespace maths {

	class Matrix4 {
	private:
		union {
			float elements[4 * 4];
			Vector4 columns[4];
		};

		void LoadRows(__m128* xmm) const;
		void LoadColumns(__m128* xmm) const;

	public:
		Matrix4(float diagonal = 0.0f);

		friend Matrix4 operator*(Matrix4 left, const Matrix4& right);
		friend Vector4 operator*(Matrix4 left, const Vector4& right);
		friend Vector3 operator*(Matrix4 left, const Vector3& right);
		friend Vector2 operator*(Matrix4 left, const Vector2& right);

		Matrix4 operator*=(const Matrix4& other);
		Vector4 operator*=(const Vector4& other);
		Vector3 operator*=(const Vector3& other);
		Vector2 operator*=(const Vector2& other);

		inline float& operator[](unsigned int i) { return elements[i]; }
	};

} }