#pragma once

#include "Keys.hpp"

namespace ht { namespace core {

#define HT_MAX_MOUSE_BUTTONS 10
#define HT_MAX_KEYBOARD_KEYS 65535

	enum class Modifier {
		SHIFT = 0x1,
		CTRL = 0x10,
		ALT = 0x100,
		ALTGR = 0x200
	};

	struct Event {
		float m_MouseX, m_MouseY;
		bool m_MouseButtons[HT_MAX_MOUSE_BUTTONS];
		char m_KeyboardKeys[HT_MAX_KEYBOARD_KEYS];

		Event() {
			m_MouseX = -1.f;
			m_MouseY = -1.f;
			memset(m_MouseButtons, 0, HT_MAX_MOUSE_BUTTONS);
			memset(m_KeyboardKeys, 0, HT_MAX_KEYBOARD_KEYS);
		}

		bool HasModifier(Modifier modifier) const {
			switch (modifier) {
			case Modifier::SHIFT:
				return m_KeyboardKeys[HT_KEY_LEFT_SHIFT] || m_KeyboardKeys[HT_KEY_RIGHT_SHIFT];
			case Modifier::CTRL:
				return m_KeyboardKeys[HT_KEY_LEFT_CONTROL] || m_KeyboardKeys[HT_KEY_RIGHT_CONTROL];
			case Modifier::ALT:
				return m_KeyboardKeys[HT_KEY_LEFT_ALT];
			case Modifier::ALTGR:
				return m_KeyboardKeys[HT_KEY_RIGHT_ALT];
			}
		}

	};

} }