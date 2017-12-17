#pragma once

#include <iostream>

#include "Keys.hpp"

#include "utils/Log.hpp"

namespace ht { namespace core {

#define HT_MAX_MOUSE_BUTTONS 10
#define HT_MAX_KEYBOARD_KEYS 65535

	enum class Modifier {
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

	struct Event {
		EventType m_EventType;
		union {
			struct {
				float x, y;
				char mouseButton;
				char mouseButtonState;
			} m_Mouse;

			struct {
				char keyboard;
				char state;
				int modifiers;
			} m_Key;
		};

		Event() {
			m_EventType = EventType::UNKNOWN;
			m_Mouse.x = -1.f;
			m_Mouse.y = -1.f;
			m_Mouse.mouseButton = -1;
			m_Mouse.mouseButtonState - 1;
		}

		bool HasModifier(Modifier modifier) const {
			HT_ASSERT(m_EventType != EventType::KEYBOARD, "[Event] Can't check modifier if event is not keyboard type.");
		}

	};

} }