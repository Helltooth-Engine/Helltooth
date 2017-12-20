#pragma once

#include "Vector2.hpp"
#include "Vector3.hpp"

#include "core/Internal.hpp"

namespace ht { namespace maths {

	struct Vector4 {
		f32 x, y, z, w;

		Vector4();
		Vector4(f32 x, f32 y, f32 z, f32 w);
		Vector4(Vector2 xy, f32 z = 0.0f, f32 w = 0.0f);
		Vector4(Vector3 xyz, f32 w = 0.0f);

		friend Vector4 operator+(Vector4 left, const Vector4& right);
		friend Vector4 operator-(Vector4 left, const Vector4& right);
		friend Vector4 operator*(Vector4 left, const Vector4& right);
		friend Vector4 operator/(Vector4 left, const Vector4& right);

		void operator+=(const Vector4& other);
		void operator-=(const Vector4& other);
		void operator*=(const Vector4& other);
		void operator/=(const Vector4& other);

		friend Vector4 operator+(Vector4 left, f32 right);
		friend Vector4 operator-(Vector4 left, f32 right);
		friend Vector4 operator*(Vector4 left, f32 right);
		friend Vector4 operator/(Vector4 left, f32 right);

		void operator+=(f32 other);
		void operator-=(f32 other);
		void operator*=(f32 other);
		void operator/=(f32 other);

		inline bool operator==(const Vector4& other) { return (x == other.x) && (y == other.y) && (z == other.z) && (w == other.w); }
		inline bool operator!=(const Vector4& other) { return (x != other.x) || (y != other.y) || (z != other.z) || (w != other.w); }
	};

} }