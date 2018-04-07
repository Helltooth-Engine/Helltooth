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
			eventType = EventType::UNKNOWN;
			mouse.x = -1.f;
			mouse.y = -1.f;
			mouse.mouseButton = -1;
			mouse.mouseButtonState = State::UNKNOWN;
		}
	};

} }