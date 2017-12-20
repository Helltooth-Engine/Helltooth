#pragma once

#include "core/Internal.hpp"

namespace ht { namespace maths {

	struct Vector2 {
		f32 x, y;

		Vector2();
		Vector2(f32 x, f32 y);

		friend Vector2 operator+(Vector2 left, const Vector2& right);
		friend Vector2 operator-(Vector2 left, const Vector2& right);
		friend Vector2 operator*(Vector2 left, const Vector2& right);
		friend Vector2 operator/(Vector2 left, const Vector2& right);

		void operator+=(const Vector2& other);
		void operator-=(const Vector2& other);
		void operator*=(const Vector2& other);
		void operator/=(const Vector2& other);

		friend Vector2 operator+(Vector2 left, f32 right);
		friend Vector2 operator-(Vector2 left, f32 right);
		friend Vector2 operator*(Vector2 left, f32 right);
		friend Vector2 operator/(Vector2 left, f32 right);

		void operator+=(f32 other);
		void operator-=(f32 other);
		void operator*=(f32 other);
		void operator/=(f32 other);

		inline bool operator==(const Vector2& other) { return (x == other.x) && (y == other.y); }
		inline bool operator!=(const Vector2& other) { return (x != other.x) || (y != other.y); }
	};

} }