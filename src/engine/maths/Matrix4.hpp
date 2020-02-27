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

#pragma once

#include <string.h>
#include <math.h>

#include "core/Internal.hpp"

#include "maths/Mathcommon.hpp"
#include "maths/Vector2.hpp"
#include "maths/Vector3.hpp"
#include "maths/Vector4.hpp"

namespace ht { namespace maths {

	class Matrix4 {
	private:
		union {
			f32 elements[4 * 4];
			Vector4 columns[4];
		};

		void LoadRows(__m128* xmm) const;
		void LoadColumns(__m128* xmm) const;

	public:
		Matrix4(f32 diagonal = 0.0f);

		static Matrix4 CreatePerspective(f32 fieldOfView, f32 nearPlane, f32 farPlane, f32 aspectRatio);
		static Matrix4 CreateOrthographic(f32 left, f32 right, f32 top, f32 bottom, f32 near, f32 far);

		Matrix4& Translate(f32 x, f32 y, f32 z);
		Matrix4& Translate(const Vector3& translation);

		Matrix4& Scale(f32 x, f32 y, f32 z);
		Matrix4& Scale(const Vector3& scale);

		Matrix4& Rotate(f32 x, f32 y, f32 z);
		Matrix4& Rotate(const Vector3& rotation);

		Matrix4& Transpose();

		Matrix4 Inverse();

		friend Matrix4 operator*(const Matrix4& left, const Matrix4& right);
		friend Vector4 operator*(const Matrix4& left, const Vector4& right);
		friend Vector3 operator*(const Matrix4& left, const Vector3& right);
		friend Vector2 operator*(const Matrix4& left, const Vector2& right);

		Matrix4 operator*=(const Matrix4& other);
		Vector4 operator*=(const Vector4& other);
		Vector3 operator*=(const Vector3& other);
		Vector2 operator*=(const Vector2& other);

		inline f32& operator[](unsigned int i) { return elements[i]; }
	};

} }