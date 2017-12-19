#pragma once
#include "Vector2.hpp"
#include "Vector3.hpp"

namespace ht { namespace maths {

	struct Vector4 {
		float x, y, z, w;

		Vector4();
		Vector4(float x, float y, float z, float w);
		Vector4(Vector2 xy, float z = 0.0f, float w = 0.0f);
		Vector4(Vector3 xyz, float w = 0.0f);

		friend Vector4 operator+(Vector4 left, const Vector4& right);
		friend Vector4 operator-(Vector4 left, const Vector4& right);
		friend Vector4 operator*(Vector4 left, const Vector4& right);
		friend Vector4 operator/(Vector4 left, const Vector4& right);

		void operator+=(const Vector4& other);
		void operator-=(const Vector4& other);
		void operator*=(const Vector4& other);
		void operator/=(const Vector4& other);

		friend Vector4 operator+(Vector4 left, float right);
		friend Vector4 operator-(Vector4 left, float right);
		friend Vector4 operator*(Vector4 left, float right);
		friend Vector4 operator/(Vector4 left, float right);

		void operator+=(float other);
		void operator-=(float other);
		void operator*=(float other);
		void operator/=(float other);

		inline bool operator==(const Vector4& other) { return (x == other.x) && (y == other.y) && (z == other.z) && (w == other.w); }
		inline bool operator!=(const Vector4& other) { return (x != other.x) || (y != other.y) || (z != other.z) || (w != other.w); }
	};

} }