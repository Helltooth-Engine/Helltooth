#pragma once
#include <Windows.h>
#include <tchar.h>

#include <stdio.h>
#include <string>

#include "graphics/Context.hpp"
#include "utils/Log.hpp"

namespace ht { namespace core {

	class Window {
	private:
		int m_Width, m_Height;
		bool m_IsVisible;
		unsigned int m_VSync;
		std::wstring m_Title;
		HWND m_Hwnd;
		graphics::Context* m_Context;

		bool m_ShouldClose = false;

	public:
		Window(std::wstring title, int width, int height);
		~Window();

		void SetVisible(bool visible);
		void Update();
		void Clear();

		inline bool WindowShouldClose() { return m_ShouldClose; }
	};

} }
