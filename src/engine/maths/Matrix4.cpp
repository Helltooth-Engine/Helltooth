﻿/*
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

#include "Matrix4.hpp"

namespace ht { namespace maths {

	Matrix4::Matrix4(f32 diagonal) {
		memset(elements, 0, 4 * 4 * sizeof(f32));
		
		if (diagonal) {
			elements[0 + 0 * 4] = diagonal;
			elements[1 + 1 * 4] = diagonal;
			elements[2 + 2 * 4] = diagonal;
			elements[3 + 3 * 4] = diagonal;
		}
	}

	void Matrix4::LoadRows(__m128* xmm) const {
		xmm[0] = _mm_set_ps(elements[0 + 3 * 4], elements[0 + 2 * 4], elements[0 + 1 * 4], elements[0 + 0 * 4]);
		xmm[1] = _mm_set_ps(elements[1 + 3 * 4], elements[1 + 2 * 4], elements[1 + 1 * 4], elements[1 + 0 * 4]);
		xmm[2] = _mm_set_ps(elements[2 + 3 * 4], elements[2 + 2 * 4], elements[2 + 1 * 4], elements[2 + 0 * 4]);
		xmm[3] = _mm_set_ps(elements[3 + 3 * 4], elements[3 + 2 * 4], elements[3 + 1 * 4], elements[3 + 0 * 4]);
	}

	void Matrix4::LoadColumns(__m128* xmm) const {
		xmm[0] = _mm_set_ps(elements[3 + 0 * 4], elements[2 + 0 * 4], elements[1 + 0 * 4], elements[0 + 0 * 4]);
		xmm[1] = _mm_set_ps(elements[3 + 1 * 4], elements[2 + 1 * 4], elements[1 + 1 * 4], elements[0 + 1 * 4]);
		xmm[2] = _mm_set_ps(elements[3 + 2 * 4], elements[2 + 2 * 4], elements[1 + 2 * 4], elements[0 + 2 * 4]);
		xmm[3] = _mm_set_ps(elements[3 + 3 * 4], elements[2 + 3 * 4], elements[1 + 3 * 4], elements[0 + 3 * 4]);
	}

	Matrix4 Matrix4::CreatePerspective(f32 fieldOfView, f32 nearPlane, f32 farPlane, f32 aspectRatio) {
		Matrix4 result = Matrix4();

		f32 tanHalf = tanh(ToRadians(fieldOfView) / 2.0f);

		result[0 + 0 * 4] =  1.0f / (tanHalf * aspectRatio);
		result[1 + 1 * 4] =  1.0f / tanHalf;
		result[2 + 2 * 4] = -(farPlane + nearPlane) / (farPlane - nearPlane);
		result[3 + 2 * 4] = -1.0f;
		result[2 + 3 * 4] = -(2.0f * farPlane * nearPlane) / (farPlane - nearPlane);
		result[3 + 3 * 4] =  0.0f;

		return result;
	}

	Matrix4 Matrix4::CreateOrthographic(f32 left, f32 right, f32 top, f32 bottom, f32 near, f32 far) {
		Matrix4 result = Matrix4(1.0f);

		result[0 + 0 * 4] = 2.0f / (right - left);
		result[1 + 1 * 4] = 2.0f / (top - bottom);
		result[2 + 2 * 4] = 2.0f / (near - far);
		result[0 + 3 * 4] = (left + right) / (left - right);
		result[1 + 3 * 4] = (bottom + top) / (bottom - top);
		result[2 + 3 * 4] = (far + near) / (far - near);
		
		return result;
	}

	Matrix4& Matrix4::Transpose() {
		f32 tmp[16];
		memcpy(tmp, elements, sizeof(elements));

		for (u32 y = 0; y < 4; y++) {
			for (u32 x = 0; x < 4; x++) {
				elements[y + x * 4] = tmp[x + y * 4];
			}
		}
		return *this;
	}

	Matrix4 Matrix4::Inverse() {
		f32 tmp[16];
		tmp[0] = elements[5] * elements[10] * elements[15] -
			elements[5] * elements[11] * elements[14] -
			elements[9] * elements[6] * elements[15] +
			elements[9] * elements[7] * elements[14] +
			elements[13] * elements[6] * elements[11] -
			elements[13] * elements[7] * elements[10];

		tmp[4] = -elements[4] * elements[10] * elements[15] +
			elements[4] * elements[11] * elements[14] +
			elements[8] * elements[6] * elements[15] -
			elements[8] * elements[7] * elements[14] -
			elements[12] * elements[6] * elements[11] +
			elements[12] * elements[7] * elements[10];

		tmp[8] = elements[4] * elements[9] * elements[15] -
			elements[4] * elements[11] * elements[13] -
			elements[8] * elements[5] * elements[15] +
			elements[8] * elements[7] * elements[13] +
			elements[12] * elements[5] * elements[11] -
			elements[12] * elements[7] * elements[9];

		tmp[12] = -elements[4] * elements[9] * elements[14] +
			elements[4] * elements[10] * elements[13] +
			elements[8] * elements[5] * elements[14] -
			elements[8] * elements[6] * elements[13] -
			elements[12] * elements[5] * elements[10] +
			elements[12] * elements[6] * elements[9];

		tmp[1] = -elements[1] * elements[10] * elements[15] +
			elements[1] * elements[11] * elements[14] +
			elements[9] * elements[2] * elements[15] -
			elements[9] * elements[3] * elements[14] -
			elements[13] * elements[2] * elements[11] +
			elements[13] * elements[3] * elements[10];

		tmp[5] = elements[0] * elements[10] * elements[15] -
			elements[0] * elements[11] * elements[14] -
			elements[8] * elements[2] * elements[15] +
			elements[8] * elements[3] * elements[14] +
			elements[12] * elements[2] * elements[11] -
			elements[12] * elements[3] * elements[10];

		tmp[9] = -elements[0] * elements[9] * elements[15] +
			elements[0] * elements[11] * elements[13] +
			elements[8] * elements[1] * elements[15] -
			elements[8] * elements[3] * elements[13] -
			elements[12] * elements[1] * elements[11] +
			elements[12] * elements[3] * elements[9];

		tmp[13] = elements[0] * elements[9] * elements[14] -
			elements[0] * elements[10] * elements[13] -
			elements[8] * elements[1] * elements[14] +
			elements[8] * elements[2] * elements[13] +
			elements[12] * elements[1] * elements[10] -
			elements[12] * elements[2] * elements[9];

		tmp[2] = elements[1] * elements[6] * elements[15] -
			elements[1] * elements[7] * elements[14] -
			elements[5] * elements[2] * elements[15] +
			elements[5] * elements[3] * elements[14] +
			elements[13] * elements[2] * elements[7] -
			elements[13] * elements[3] * elements[6];

		tmp[6] = -elements[0] * elements[6] * elements[15] +
			elements[0] * elements[7] * elements[14] +
			elements[4] * elements[2] * elements[15] -
			elements[4] * elements[3] * elements[14] -
			elements[12] * elements[2] * elements[7] +
			elements[12] * elements[3] * elements[6];

		tmp[10] = elements[0] * elements[5] * elements[15] -
			elements[0] * elements[7] * elements[13] -
			elements[4] * elements[1] * elements[15] +
			elements[4] * elements[3] * elements[13] +
			elements[12] * elements[1] * elements[7] -
			elements[12] * elements[3] * elements[5];

		tmp[14] = -elements[0] * elements[5] * elements[14] +
			elements[0] * elements[6] * elements[13] +
			elements[4] * elements[1] * elements[14] -
			elements[4] * elements[2] * elements[13] -
			elements[12] * elements[1] * elements[6] +
			elements[12] * elements[2] * elements[5];

		tmp[3] = -elements[1] * elements[6] * elements[11] +
			elements[1] * elements[7] * elements[10] +
			elements[5] * elements[2] * elements[11] -
			elements[5] * elements[3] * elements[10] -
			elements[9] * elements[2] * elements[7] +
			elements[9] * elements[3] * elements[6];

		tmp[7] = elements[0] * elements[6] * elements[11] -
			elements[0] * elements[7] * elements[10] -
			elements[4] * elements[2] * elements[11] +
			elements[4] * elements[3] * elements[10] +
			elements[8] * elements[2] * elements[7] -
			elements[8] * elements[3] * elements[6];

		tmp[11] = -elements[0] * elements[5] * elements[11] +
			elements[0] * elements[7] * elements[9] +
			elements[4] * elements[1] * elements[11] -
			elements[4] * elements[3] * elements[9] -
			elements[8] * elements[1] * elements[7] +
			elements[8] * elements[3] * elements[5];

		tmp[15] = elements[0] * elements[5] * elements[10] -
			elements[0] * elements[6] * elements[9] -
			elements[4] * elements[1] * elements[10] +
			elements[4] * elements[2] * elements[9] +
			elements[8] * elements[1] * elements[6] -
			elements[8] * elements[2] * elements[5];

		Matrix4 result;

		f32 determinant = elements[0] * tmp[0] + elements[1] * tmp[4] + elements[2] * tmp[8] + elements[3] * tmp[12];

		for (u32 i = 0; i < 16; i++)
			result[i] = tmp[i] * determinant;

		return result;
	}

	Matrix4& Matrix4::Translate(f32 x, f32 y, f32 z) {
		Matrix4 translationMat4 = Matrix4(1.0f);
		translationMat4[0 + 3 * 4] = x;
		translationMat4[1 + 3 * 4] = y;
		translationMat4[2 + 3 * 4] = z;
		*this = *this * translationMat4;
		return *this;
	}

	Matrix4& Matrix4::Translate(const Vector3& translation) {
		Matrix4 translationMat4 = Matrix4(1.0f);
		translationMat4[0 + 3 * 4] = translation.x;
		translationMat4[1 + 3 * 4] = translation.y;
		translationMat4[2 + 3 * 4] = translation.z;
		*this = *this * translationMat4;
		return *this;
	}

	Matrix4& Matrix4::Scale(f32 x, f32 y, f32 z) {
		Matrix4 scaleMatrix = Matrix4(1.0f);
		scaleMatrix[0 + 0 * 4] = x;
		scaleMatrix[1 + 1 * 4] = y;
		scaleMatrix[2 + 2 * 4] = z;
		*this = *this * scaleMatrix;
		return *this;
	}

	Matrix4& Matrix4::Scale(const Vector3& scale) {
		Matrix4 scaleMatrix = Matrix4(1.0f);
		scaleMatrix[0 + 0 * 4] = scale.x;
		scaleMatrix[1 + 1 * 4] = scale.y;
		scaleMatrix[2 + 2 * 4] = scale.z;
		*this = *this * scaleMatrix;
		return *this;
	}

	Matrix4& Matrix4::Rotate(f32 x, f32 y, f32 z) {
		return Rotate(Vector3(x, y, z));
	}

	Matrix4& Matrix4::Rotate(const Vector3& rotation) {
		Matrix4 rotx = Matrix4(1.0f);
		Matrix4 roty = Matrix4(1.0f);
		Matrix4 rotz = Matrix4(1.0f);

		f32 xcos = cosf(ToRadians(rotation.x));
		f32 xsin = sinf(ToRadians(rotation.x));
		f32 ycos = cosf(ToRadians(rotation.y));
		f32 ysin = sinf(ToRadians(rotation.y));
		f32 zcos = cosf(ToRadians(rotation.z));
		f32 zsin = sinf(ToRadians(rotation.z));

		rotx[1 + 1 * 4] = xcos;
		rotx[1 + 2 * 4] = -xsin;
		rotx[2 + 1 * 4] = xsin;
		rotx[2 + 2 * 4] = xcos;

		roty[0 + 0 * 4] = ycos;
		roty[0 + 2 * 4] = -ysin;
		roty[2 + 0 * 4] = ysin;
		roty[2 + 2 * 4] = ycos;

		rotz[0 + 0 * 4] = zcos;
		rotz[0 + 1 * 4] = -zsin;
		rotz[1 + 0 * 4] = zsin;
		rotz[1 + 1 * 4] = zcos;

		Matrix4 result = Matrix4(1.0f);
		result = rotx * roty * rotz;
		*this = *this * result;
		return *this;
	}


	Matrix4 operator*(const Matrix4& left, const Matrix4& right) {
		Matrix4 tmp;
		__m128 rows[4];
		__m128 cols[4];

		right.LoadColumns(cols);
		left.LoadRows(rows);

		for (unsigned int y = 0; y < 4; y++)
			for (unsigned int x = 0; x < 4; x++) {
				__m128 res = _mm_mul_ps(rows[x], cols[y]);
				tmp[x + y * 4] = m128_get(res, 0) + m128_get(res, 1) + m128_get(res, 2) + m128_get(res, 3);
			}
		
		return tmp;
	}

	Vector4 operator*(const Matrix4& left, const Vector4& right) {
		__m128 vec[4];
		__m128 col[4];
		
		vec[0] = _mm_set_ps(right.x, right.x, right.x, right.x);
		vec[1] = _mm_set_ps(right.y, right.y, right.y, right.y);
		vec[2] = _mm_set_ps(right.z, right.z, right.z, right.z);
		vec[3] = _mm_set_ps(right.w, right.w, right.w, right.w);

		left.LoadColumns(col);

		__m128 res = _mm_mul_ps(vec[0], col[0]);

		for (int i = 1; i < 4; i++)
			res = _mm_fmadd_ps(vec[i], col[i], res);

		return Vector4(m128_get(res, 0), m128_get(res, 1), m128_get(res, 2), m128_get(res,3));
	}

	Vector3 operator*(const Matrix4& left, const Vector3& right) {
		__m128 vec[4];
		__m128 col[4];

		vec[0] = _mm_set_ps(right.x, right.x, right.x, right.x);
		vec[1] = _mm_set_ps(right.y, right.y, right.y, right.y);
		vec[2] = _mm_set_ps(right.z, right.z, right.z, right.z);
		vec[3] = _mm_set_ps(1, 1, 1, 1);

		left.LoadColumns(col);

		__m128 res = _mm_mul_ps(vec[0], col[0]);

		for (int i = 1; i < 4; i++)
			res = _mm_fmadd_ps(vec[i], col[i], res);

		return Vector3(m128_get(res, 0), m128_get(res, 1), m128_get(res, 2));
	}

	Vector2 operator*(const Matrix4& left, const Vector2& right) {
		__m128 vec[4];
		__m128 col[4];

		vec[0] = _mm_set_ps(right.x, right.x, right.x, right.x);
		vec[1] = _mm_set_ps(right.y, right.y, right.y, right.y);
		vec[2] = _mm_set_ps(1, 1, 1, 1);
		vec[3] = _mm_set_ps(1, 1, 1, 1);

		left.LoadColumns(col);

		__m128 res = _mm_mul_ps(vec[0], col[0]);

		for (int i = 1; i < 4; i++)
			res = _mm_fmadd_ps(vec[i], col[i], res);

		return Vector2(m128_get(res, 0), m128_get(res, 1));
	}

	Matrix4 Matrix4::operator*=(const Matrix4& other) {
		return (*this) * other;
	}

	Vector4 Matrix4::operator*=(const Vector4& other) {
		return (*this) * other;
	}

	Vector3 Matrix4::operator*=(const Vector3& other) {
		return (*this) * other;
	}

	Vector2 Matrix4::operator*=(const Vector2& other) {
		return (*this) * other;
	}

} }