#include "EventListener.hpp"

namespace ht { namespace core {

	bool EventListener::OnMove(f32 x, f32 y) {
		HT_MSG("[EventListener] OnMove not implemented for %s.", m_Name.GetData());
		return false;
	}

	bool EventListener::OnPress(f32 x, f32 y) {
		HT_MSG("[EventListener] OnPress not implemented for %s.", m_Name.GetData());
		return false;
	}

	bool EventListener::OnRelease(f32 x, f32 y)  {
		HT_MSG("[EventListener] OnRelease not implemented for %s.", m_Name.GetData());
		return false;
	}

	bool EventListener::OnScroll(f32 xOffset) {
		HT_MSG("[EventListener] OnScroll not implemented for %s.", m_Name.GetData());
		return false;
	}

	bool EventListener::OnKeyPress(u16 key, u16 modifier) {
		HT_MSG("[EventListener] OnKeyPress not implemented for %s.", m_Name.GetData());
		return false;
	}

	bool EventListener::OnKeyRepeat(u16 key, u16 modifier) {
		HT_MSG("[EventListener] OnKeyRepeat not implemented for %s.", m_Name.GetData());
		return false;
	}

	bool EventListener::OnKeyRelease(u16 key) {
		HT_MSG("[EventListener] OnKeyRelease not implemented for %s.", m_Name.GetData());
		return false;
	}

} }