#include "Vector3.hpp"

namespace ht { namespace maths {

	Vector3::Vector3() : x(0), y(0), z(0) {}
	Vector3::Vector3(f32 x, f32 y, f32 z) : x(x), y(y), z(z) {}
	Vector3::Vector3(Vector2 xy, f32 z) : x(xy.x), y(xy.y), z(z) {}

	Vector3 operator+(Vector3 left, const Vector3& right) {
		left.x += right.x;
		left.y += right.y;
		left.z += right.z;
		return left;
	}

	Vector3 operator-(Vector3 left, const Vector3& right) {
		left.x -= right.x;
		left.y -= right.y;
		left.z -= right.z;
		return left;
	}

	Vector3 operator*(Vector3 left, const Vector3& right) {
		left.x *= right.x;
		left.y *= right.y;
		left.z *= right.z;
		return left;
	}

	Vector3 operator/(Vector3 left, const Vector3& right) {
		left.x /= right.x;
		left.y /= right.y;
		left.z /= right.z;
		return left;
	}

	void Vector3::operator+=(const Vector3& other) {
		x += other.x;
		y += other.y;
		z += other.z;
	}

	void Vector3::operator-=(const Vector3& other) {
		x -= other.x;
		y -= other.y;
		z -= other.z;
	}

	void Vector3::operator*=(const Vector3& other) {
		x *= other.x;
		y *= other.y;
		z *= other.z;
	}

	void Vector3::operator/=(const Vector3& other) {
		x /= other.x;
		y /= other.y;
		z /= other.z;
	}

	Vector3 operator+(Vector3 left, f32 right) {
		left.x += right;
		left.y += right;
		left.z += right;
		return left;
	}

	Vector3 operator-(Vector3 left, f32 right) {
		left.x -= right;
		left.y -= right;
		left.z -= right;
		return left;
	}

	Vector3 operator*(Vector3 left, f32 right) {
		left.x *= right;
		left.y *= right;
		left.z *= right;
		return left;
	}

	Vector3 operator/(Vector3 left, f32 right) {
		left.x /= right;
		left.y /= right;
		left.z /= right;
		return left;
	}

	void Vector3::operator+=(f32 other) {
		x += other;
		y += other;
		z += other;
	}

	void Vector3::operator-=(f32 other) {
		x -= other;
		y -= other;
		z -= other;
	}

	void Vector3::operator*=(f32 other) {
		x *= other;
		y *= other;
		z *= other;
	}

	void Vector3::operator/=(f32 other) {
		x /= other;
		y /= other;
		z /= other;
	}

} }