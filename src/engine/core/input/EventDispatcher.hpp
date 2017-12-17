#pragma once

#include <vector>

#include "EventListener.hpp"

namespace ht { namespace core {
	
	class EventDispatcher {
	private:
		static std::vector<EventListener*> s_EventListeners;

	public:
		static void Dispatch(Event* e);

		static void Add(EventListener* listener);
		static void Remove(EventListener* listener);

	};

} }