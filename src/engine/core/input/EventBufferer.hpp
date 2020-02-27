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

#include "EventListener.hpp"

namespace ht { namespace core {

	class EventBufferer : public EventListener {
	protected:
		bool m_Keys[HT_MAX_KEYBOARD_KEYS];
		bool m_MouseKeys[HT_MAX_MOUSE_BUTTONS];
		
		float m_MouseX, m_MouseY;
		float m_Scroll;

	public:
		EventBufferer(utils::String name) 
			: EventListener(name), m_MouseX(-1.0f), m_MouseY(-1.0f), m_Scroll(0.0f) {
			memset(m_Keys, 0, HT_MAX_KEYBOARD_KEYS);
			memset(m_MouseKeys, 0, HT_MAX_MOUSE_BUTTONS);
		}

		virtual bool OnMove(f32 x, f32 y);
		virtual bool OnPress(u8 button, f32 x, f32 y);
		virtual bool OnRelease(u8 button, f32 x, f32 y);

		virtual bool OnScroll(f32 xOffset);

		virtual bool OnKeyPress(u16 key, u16 modifier);
		virtual bool OnKeyRepeat(u16 key, u16 modifier);
		virtual bool OnKeyRelease(u16 key);

	};

} }