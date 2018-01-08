#include "EventBufferer.hpp"

namespace ht { namespace core {
	
	bool EventBufferer::OnMove(f32 x, f32 y) {
		m_MouseX = x;
		m_MouseY = y;
	}

	bool EventBufferer::OnPress(u8 button, f32 x, f32 y) {
		m_MouseX = x;
		m_MouseY = y;
		m_MouseKeys[button] = true;
	}

	bool EventBufferer::OnRelease(u8 button, f32 x, f32 y) {
		m_MouseX = x;
		m_MouseY = y;
		m_MouseKeys[button] = false;
	}

	bool EventBufferer::OnScroll(f32 xOffset) {
		m_Scroll += xOffset;
	}

	bool EventBufferer::OnKeyPress(u16 key, u16 modifier) {
		m_Keys[key] = true;
	}

	bool EventBufferer::OnKeyRepeat(u16 key, u16 modifier) {

	}

	bool EventBufferer::OnKeyRelease(u16 key) {
		m_Keys[key] = false;
	}

} }