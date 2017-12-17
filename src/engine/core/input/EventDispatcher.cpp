#include "EventDispatcher.hpp"

namespace ht { namespace core {

	void EventDispatcher::Dispatch(Event* e) {
		HT_ASSERT(e == nullptr, "Event cannot be nullptr!");

	}

	void EventDispatcher::Add(EventListener* listener) {
		HT_ASSERT(listener == nullptr, "EventListener cannot be nullptr!");
		s_EventListeners.push_back(listener);
	}

	void EventDispatcher::Remove(EventListener* listener) {
		HT_ASSERT(listener == nullptr, "EventListener cannot be nullptr!");
		for (int i = 0; i < s_EventListeners.size(); i++)
			if (s_EventListeners[i] == listener) {
				s_EventListeners.erase(s_EventListeners.begin() + i);
				break;
			}
	}


} }