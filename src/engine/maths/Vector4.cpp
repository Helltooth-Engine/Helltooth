#include "Vector4.hpp"

namespace ht { namespace maths {

	Vector4::Vector4() : x(0), y(0), z(0), w(0) {}
	Vector4::Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
	Vector4::Vector4(Vector2 xy, float z, float w) : x(xy.x), y(xy.y), z(z), w(w) {}
	Vector4::Vector4(Vector3 xyz, float w) : x(xyz.x), y(xyz.y), z(xyz.z), w(w) {}

	Vector4 operator+(Vector4 left, const Vector4& right) {
		left.x += right.x;
		left.y += right.y;
		left.z += right.z;
		left.w += right.w;
		return left;
	}

	Vector4 operator-(Vector4 left, const Vector4& right) {
		left.x -= right.x;
		left.y -= right.y;
		left.z -= right.z;
		left.w -= right.w;
		return left;
	}

	Vector4 operator*(Vector4 left, const Vector4& right) {
		left.x *= right.x;
		left.y *= right.y;
		left.z *= right.z;
		left.w *= right.w;
		return left;
	}

	Vector4 operator/(Vector4 left, const Vector4& right) {
		left.x /= right.x;
		left.y /= right.y;
		left.z /= right.z;
		left.w /= right.w;
		return left;
	}

	void Vector4::operator+=(const Vector4& other) {
		x += other.x;
		y += other.y;
		z += other.z;
		w += other.w;
	}

	void Vector4::operator-=(const Vector4& other) {
		x -= other.x;
		y -= other.y;
		z -= other.z;
		w -= other.w;
	}

	void Vector4::operator*=(const Vector4& other) {
		x *= other.x;
		y *= other.y;
		z *= other.z;
		w *= other.w;
	}

	void Vector4::operator/=(const Vector4& other) {
		x /= other.x;
		y /= other.y;
		z /= other.z;
		w /= other.w;
	}

	Vector4 operator+(Vector4 left, float right) {
		left.x += right;
		left.y += right;
		left.z += right;
		left.w += right;
		return left;
	}

	Vector4 operator-(Vector4 left, float right) {
		left.x -= right;
		left.y -= right;
		left.z -= right;
		left.w -= right;
		return left;
	}

	Vector4 operator*(Vector4 left, float right) {
		left.x *= right;
		left.y *= right;
		left.z *= right;
		left.w *= right;
		return left;
	}

	Vector4 operator/(Vector4 left, float right) {
		left.x /= right;
		left.y /= right;
		left.z /= right;
		left.w /= right;
		return left;
	}

	void Vector4::operator+=(float other) {
		x += other;
		y += other;
		z += other;
		w += other;
	}

	void Vector4::operator-=(float other) {
		x -= other;
		y -= other;
		z -= other;
		w -= other;
	}

	void Vector4::operator*=(float other) {
		x *= other;
		y *= other;
		z *= other;
		w *= other;
	}

	void Vector4::operator/=(float other) {
		x /= other;
		y /= other;
		z /= other;
		w /= other;
	}

} }