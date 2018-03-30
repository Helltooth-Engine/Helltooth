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