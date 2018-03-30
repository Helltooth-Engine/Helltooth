#pragma once

#include <vector>

#include "core/Internal.hpp"

#include "core/input/EventListener.hpp"

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