/*
 * Copyright (c) 2020 Rareș-Nicolaie Ciorbă
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

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