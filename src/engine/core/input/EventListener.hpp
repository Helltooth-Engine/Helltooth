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

		virtual void OnMove(float x, float y);
		virtual void OnPress(float x, float y);
		virtual void OnRelease(float x, float y);

		virtual void OnScroll(float xOffset);

		virtual void OnKeyPress(int key, unsigned short modifier);
		virtual void OnKeyRepeat(int key, unsigned short modifier);
		virtual void OnKeyRelease(int key);
	};


} }