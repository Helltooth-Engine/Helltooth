#pragma once
#include "Event.hpp"
#include "utils/Log.hpp"
#include "utils/String.hpp"

namespace ht { namespace core {

	class EventListener {
	private:
		utils::String m_Name;

	public:
		EventListener(utils::String name) : m_Name(name) {}

		virtual bool OnMove(float x, float y);
		virtual bool OnPress(float x, float y);
		virtual bool OnRelease(float x, float y);

		virtual bool OnScroll(float xOffset);

		virtual bool OnKeyPress(int key, unsigned short modifier);
		virtual bool OnKeyRepeat(int key, unsigned short modifier);
		virtual bool OnKeyRelease(int key);
	};


} }