#pragma once

namespace ht { namespace maths {

	struct Vector2 {
		float x, y;

		Vector2();
		Vector2(float x, float y);

		friend Vector2 operator+(Vector2 left, const Vector2& right);
		friend Vector2 operator-(Vector2 left, const Vector2& right);
		friend Vector2 operator*(Vector2 left, const Vector2& right);
		friend Vector2 operator/(Vector2 left, const Vector2& right);

		void operator+=(const Vector2& other);
		void operator-=(const Vector2& other);
		void operator*=(const Vector2& other);
		void operator/=(const Vector2& other);

		friend Vector2 operator+(Vector2 left, float right);
		friend Vector2 operator-(Vector2 left, float right);
		friend Vector2 operator*(Vector2 left, float right);
		friend Vector2 operator/(Vector2 left, float right);

		void operator+=(float other);
		void operator-=(float other);
		void operator*=(float other);
		void operator/=(float other);

		inline bool operator==(const Vector2& other) { return (x == other.x) && (y == other.y); }
		inline bool operator!=(const Vector2& other) { return (x != other.x) || (y != other.y); }
	};

} }