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

#include "core/Internal.hpp"

#include "core/input/Event.hpp"

#include "utils/Log.hpp"
#include "utils/String.hpp"

namespace ht { namespace core {

	class EventListener {
	private:
		utils::String m_Name;

	public:
		EventListener(utils::String name) : m_Name(name) {}

		virtual bool OnMove(f32 x, f32 y);
		virtual bool OnPress(u8 button, f32 x, f32 y);
		virtual bool OnRelease(u8 button, f32 x, f32 y);

		virtual bool OnScroll(f32 xOffset);

		virtual bool OnKeyPress(u16 key, u16 modifier);
		virtual bool OnKeyRepeat(u16 key, u16 modifier);
		virtual bool OnKeyRelease(u16 key);
	};


} }