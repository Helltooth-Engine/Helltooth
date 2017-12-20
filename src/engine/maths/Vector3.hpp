#pragma once
#include "Vector2.hpp"

#include "core/Internal.hpp"

namespace ht { namespace maths {

	struct Vector3 {
		f32 x, y, z;

		Vector3();
		Vector3(f32 x, f32 y, f32 z);
		Vector3(Vector2 xy, f32 z = 0.0f);

		friend Vector3 operator+(Vector3 left, const Vector3& right);
		friend Vector3 operator-(Vector3 left, const Vector3& right);
		friend Vector3 operator*(Vector3 left, const Vector3& right);
		friend Vector3 operator/(Vector3 left, const Vector3& right);

		void operator+=(const Vector3& other);
		void operator-=(const Vector3& other);
		void operator*=(const Vector3& other);
		void operator/=(const Vector3& other);

		friend Vector3 operator+(Vector3 left, f32 right);
		friend Vector3 operator-(Vector3 left, f32 right);
		friend Vector3 operator*(Vector3 left, f32 right);
		friend Vector3 operator/(Vector3 left, f32 right);

		void operator+=(f32 other);
		void operator-=(f32 other);
		void operator*=(f32 other);
		void operator/=(f32 other);

		inline bool operator==(const Vector3& other) { return (x == other.x) && (y == other.y) && (z == other.z); }
		inline bool operator!=(const Vector3& other) { return (x != other.x) || (y != other.y) || (z != other.z); }
	};

} }