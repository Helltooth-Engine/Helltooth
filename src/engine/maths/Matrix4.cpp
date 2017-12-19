#include "Matrix4.hpp"

namespace ht { namespace maths {

	Matrix4::Matrix4(float diagonal = 0.0f) {
		memset(elements, 0, 4 * 4 * sizeof(float));
		
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


	Matrix4 operator*(Matrix4 left, const Matrix4& right) {
		Matrix4 tmp;
		__m128 rows[4];
		__m128 cols[4];

		right.LoadColumns(cols);
		left.LoadRows(rows);

		for (unsigned int y = 0; y < 4; y++)
			for (unsigned int x = 0; x < 4; x++) {
				__m128 res = _mm_mul_ps(rows[x], cols[y]);
				tmp[x + y * 4] = res.m128_f32[0] + res.m128_f32[1] + res.m128_f32[2] + res.m128_f32[3];
			}
		
		return tmp;
	}

	Vector4 operator*(Matrix4 left, const Vector4& right) {
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

		return Vector4(res.m128_f32[0], res.m128_f32[1], res.m128_f32[2], res.m128_f32[3]);
	}

	Vector3 operator*(Matrix4 left, const Vector3& right) {
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

		return Vector3(res.m128_f32[0], res.m128_f32[1], res.m128_f32[2]);
	}

	Vector2 operator*(Matrix4 left, const Vector2& right) {
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

		return Vector2(res.m128_f32[0], res.m128_f32[1]);
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