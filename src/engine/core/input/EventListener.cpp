#include "EventListener.hpp"

namespace ht { namespace core {

	bool EventListener::OnMove(float x, float y) {
		HT_MSG("[EventListener] OnMove not implemented for %s.", m_Name.GetData());
		return false;
	}

	bool EventListener::OnPress(float x, float y) {
		HT_MSG("[EventListener] OnPress not implemented for %s.", m_Name.GetData());
		return false;
	}

	bool EventListener::OnRelease(float x, float y)  {
		HT_MSG("[EventListener] OnRelease not implemented for %s.", m_Name.GetData());
		return false;
	}

	bool EventListener::OnScroll(float xOffset) {
		HT_MSG("[EventListener] OnScroll not implemented for %s.", m_Name.GetData());
		return false;
	}

	bool EventListener::OnKeyPress(int key, unsigned short modifier) {
		HT_MSG("[EventListener] OnKeyPress not implemented for %s.", m_Name.GetData());
		return false;
	}

	bool EventListener::OnKeyRepeat(int key, unsigned short modifier) {
		HT_MSG("[EventListener] OnKeyRepeat not implemented for %s.", m_Name.GetData());
		return false;
	}

	bool EventListener::OnKeyRelease(int key) {
		HT_MSG("[EventListener] OnKeyRelease not implemented for %s.", m_Name.GetData());
		return false;
	}

} }