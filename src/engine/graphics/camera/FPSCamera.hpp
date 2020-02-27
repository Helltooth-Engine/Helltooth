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

#pragma once

#include "Camera.hpp"

namespace ht { namespace graphics {

	class FPSCamera : public Camera {
	private:
		f32 m_SpeedFactor = 10; // 10 units / second 
		f32 m_YawSensitivity = 0.2f; // degrees / second
		f32 m_PitchSensitivty = 0.2f; // degres / second
		
		maths::Vector2 m_MouseLast;

	public:
		FPSCamera(const maths::Vector3& position);
		FPSCamera(f32 x, f32 y, f32 z);

		void Update(f32 delta) override;

	};

} }