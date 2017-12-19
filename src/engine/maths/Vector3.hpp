#pragma once
#include "Vector2.hpp"

namespace ht { namespace maths {

	struct Vector3 {
		float x, y, z;

		Vector3();
		Vector3(float x, float y, float z);
		Vector3(Vector2 xy, float z = 0.0f);

		friend Vector3 operator+(Vector3 left, const Vector3& right);
		friend Vector3 operator-(Vector3 left, const Vector3& right);
		friend Vector3 operator*(Vector3 left, const Vector3& right);
		friend Vector3 operator/(Vector3 left, const Vector3& right);

		void operator+=(const Vector3& other);
		void operator-=(const Vector3& other);
		void operator*=(const Vector3& other);
		void operator/=(const Vector3& other);

		friend Vector3 operator+(Vector3 left, float right);
		friend Vector3 operator-(Vector3 left, float right);
		friend Vector3 operator*(Vector3 left, float right);
		friend Vector3 operator/(Vector3 left, float right);

		void operator+=(float other);
		void operator-=(float other);
		void operator*=(float other);
		void operator/=(float other);

		inline bool operator==(const Vector3& other) { return (x == other.x) && (y == other.y) && (z == other.z); }
		inline bool operator!=(const Vector3& other) { return (x != other.x) || (y != other.y) || (z != other.z); }
	};

} }