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

#include <iostream>

#include "core/Internal.hpp"

#include "core/input/Keys.hpp"

#include "utils/Log.hpp"

namespace ht { namespace core {

#define HT_MAX_MOUSE_BUTTONS        10
#define HT_MAX_KEYBOARD_KEYS        65535

	enum class Modifier {
		NONE    = 0x000,
		SHIFT   = 0x001,
		CTRL    = 0x010,
		ALT     = 0x100,
		ALTGR   = 0x200
	};
	
	enum class EventType {
		UNKNOWN   = -1,
		MOUSE     =  1,
		KEYBOARD  =  2
	};

	enum class State {
		UNKNOWN   = -1,
		NONE      =  0,
		RELEASED  =  1,
		PRESSED   =  2,
		REPEAT    =  3
	};

	struct Event {
		EventType eventType;
		union {
			struct {
				f32 x, y;
				s8 mouseButton;
				State mouseButtonState;
			} mouse;

			struct {
				u16 key;
				State state;
				u16 modifiers;
			} key;
		};

		Event() {
			eventType               = EventType::UNKNOWN;
			mouse.x                 = -1.f;
			mouse.y                 = -1.f;
			mouse.mouseButton       = -1;
			mouse.mouseButtonState  = State::UNKNOWN;
		}
	};

} }