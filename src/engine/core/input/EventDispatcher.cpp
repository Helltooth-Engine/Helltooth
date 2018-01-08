#include "EventDispatcher.hpp"

namespace ht { namespace core {

	std::vector<EventListener*> EventDispatcher::s_EventListeners;
	void EventDispatcher::Dispatch(Event* e) {
		HT_ASSERT(e == nullptr, "Event cannot be nullptr!");
		HT_ASSERT(e->m_EventType == EventType::UNKNOWN, "Event type unknown!");

		switch (e->m_EventType) {
		case EventType::MOUSE:
			{
				f32 x = e->m_Mouse.x;
				f32 y = e->m_Mouse.y;
				u8 button = e->m_Mouse.mouseButton;
				State state = e->m_Mouse.mouseButtonState;
				switch (state) {
				case State::PRESSED:
					for (EventListener* listener : s_EventListeners)
						listener->OnPress(button, x, y);
					break;
				case State::RELEASED:
					for (EventListener* listener : s_EventListeners)
						listener->OnRelease(button, x, y);
					break;
				case State::NONE:
					for (EventListener* listener : s_EventListeners)
						listener->OnMove(x, y);
					break;
				}
			}
			break;
		case EventType::KEYBOARD:
			{
				u16 key = e->m_Key.key;
				u16 modifier = e->m_Key.modifiers;
				State state = e->m_Key.state;
				switch (state) {
				case State::PRESSED:
					for (EventListener* listener : s_EventListeners)
						listener->OnKeyPress(key, modifier);
					break;
				case State::REPEAT:
					for (EventListener* listener : s_EventListeners)
						listener->OnKeyRepeat(key, modifier);
					break;
				case State::RELEASED:
					for (EventListener* listener : s_EventListeners)
						listener->OnKeyRelease(key);
					break;
				}
			}
			break;
		}
	}

	void EventDispatcher::Add(EventListener* listener) {
		HT_ASSERT(listener == nullptr, "EventListener cannot be nullptr!");
		s_EventListeners.push_back(listener);
	}

	void EventDispatcher::Remove(EventListener* listener) {
		HT_ASSERT(listener == nullptr, "EventListener cannot be nullptr!");
		for (u32 i = 0; i < s_EventListeners.size(); i++)
			if (s_EventListeners[i] == listener) {
				s_EventListeners.erase(s_EventListeners.begin() + i);
				break;
			}
	}


} }