#pragma once

#include "core/Internal.hpp"

#include "core/input/Event.hpp"

#include "utils/Log.hpp"
#include "utils/String.hpp"

namespace ht { namespace core {

	class EventListener {
	private:
		utils::String m_Name;

	public:
		EventListener(utils::String name) : m_Name(name) {}

		virtual bool OnMove(f32 x, f32 y);
		virtual bool OnPress(u8 button, f32 x, f32 y);
		virtual bool OnRelease(u8 button, f32 x, f32 y);

		virtual bool OnScroll(f32 xOffset);

		virtual bool OnKeyPress(u16 key, u16 modifier);
		virtual bool OnKeyRepeat(u16 key, u16 modifier);
		virtual bool OnKeyRelease(u16 key);
	};


} }