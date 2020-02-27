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

#include "EventBufferer.hpp"

namespace ht { namespace core {
	
	bool EventBufferer::OnMove(f32 x, f32 y) {
		m_MouseX = x;
		m_MouseY = y;
		return true;
	}

	bool EventBufferer::OnPress(u8 button, f32 x, f32 y) {
		m_MouseX = x;
		m_MouseY = y;
		m_MouseKeys[button] = true;
		return true;
	}

	bool EventBufferer::OnRelease(u8 button, f32 x, f32 y) {
		m_MouseX = x;
		m_MouseY = y;
		m_MouseKeys[button] = false;
		return true;
	}

	bool EventBufferer::OnScroll(f32 xOffset) {
		m_Scroll += xOffset;
		return true;
	}

	bool EventBufferer::OnKeyPress(u16 key, u16 modifier) {
		m_Keys[key] = true;
		return true;
	}

	bool EventBufferer::OnKeyRepeat(u16 key, u16 modifier) {
		// TODO: On key repeat
		return true;
	}

	bool EventBufferer::OnKeyRelease(u16 key) {
		m_Keys[key] = false;
		return true;
	}

} }