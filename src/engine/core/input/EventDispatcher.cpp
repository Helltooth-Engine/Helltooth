/*
 * Copyright (c) 2020 Rareș-Nicolaie Ciorbă
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#include "EventDispatcher.hpp"

namespace ht { namespace core {

	std::vector<EventListener*> EventDispatcher::s_EventListeners;
	void EventDispatcher::Dispatch(Event* e) {
		HT_ASSERT(e, "Event cannot be nullptr!");
		HT_ASSERT(e->eventType != EventType::UNKNOWN, "Event type unknown!");

		switch (e->eventType) {
		case EventType::MOUSE:
			{
				f32 x        = e->mouse.x;
				f32 y        = e->mouse.y;
				u8 button    = e->mouse.mouseButton;
				State state  = e->mouse.mouseButtonState;
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
				u16 key       = e->key.key;
				u16 modifier  = e->key.modifiers;
				State state   = e->key.state;
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
		HT_ASSERT(listener, "EventListener cannot be nullptr!");
		s_EventListeners.push_back(listener);
	}

	void EventDispatcher::Remove(EventListener* listener) {
		HT_ASSERT(listener, "EventListener cannot be nullptr!");
		for (u32 i = 0; i < s_EventListeners.size(); i++)
			if (s_EventListeners[i] == listener) {
				s_EventListeners.erase(s_EventListeners.begin() + i);
				break;
			}
	}

} }