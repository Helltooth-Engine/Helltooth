#pragma once

#include <iostream>

#include "Keys.hpp"

#include "core/Internal.hpp"

#include "utils/Log.hpp"

namespace ht { namespace core {

#define HT_MAX_MOUSE_BUTTONS 10
#define HT_MAX_KEYBOARD_KEYS 65535

	enum class Modifier {
		NONE = 0x0,
		SHIFT = 0x1,
		CTRL = 0x10,
		ALT = 0x100,
		ALTGR = 0x200
	};
	
	enum class EventType {
		UNKNOWN = -1,
		MOUSE = 1,
		KEYBOARD = 2
	};

	enum class State {
		UNKNOWN = -1,
		NONE = 0,
		RELEASED = 1,
		PRESSED = 2,
		REPEAT = 3,
	};

	struct Event {
		EventType m_EventType;
		union {
			struct {
				f32 x, y;
				s8 mouseButton;
				State mouseButtonState;
			} m_Mouse;

			struct {
				u16 key;
				State state;
				u16 modifiers;
			} m_Key;
		};

		Event() {
			m_EventType = EventType::UNKNOWN;
			m_Mouse.x = -1.f;
			m_Mouse.y = -1.f;
			m_Mouse.mouseButton = -1;
			m_Mouse.mouseButtonState = State::UNKNOWN;
		}
	};

} }