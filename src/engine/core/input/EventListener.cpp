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

#include "EventListener.hpp"

namespace ht { namespace core {

	bool EventListener::OnMove(f32 x, f32 y) {
		HT_MSG("[EventListener] OnMove not implemented for %s.", m_Name.GetData());
		return false;
	}

	bool EventListener::OnPress(u8 button, f32 x, f32 y) {
		HT_MSG("[EventListener] OnPress not implemented for %s.", m_Name.GetData());
		return false;
	}

	bool EventListener::OnRelease(u8 button, f32 x, f32 y)  {
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