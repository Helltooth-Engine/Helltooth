﻿/*
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

#pragma once

#ifdef HT_WINDOWS
#include <Windows.h>
#endif // HT_WINDOWS

#include <utility>
#include <stdio.h>
#include <string>
#include <map>

#ifdef HT_OPENGL
#include "platform/opengl/GL.hpp"
#endif // HT_OPENGL

#include "core/Internal.hpp"

#if defined(HT_WINDOWS)
#define HT_LEVEL_FATAL          0xC0
#define HT_LEVEL_ERROR          0x0C
#define HT_LEVEL_WARNING        0x0E
#define HT_LEVEL_INFO           0x0F
#define HT_LEVEL_MSG            0x07
#elif defined(HT_LINUX)
#define HT_LEVEL_FATAL          "\033[0;31m"
#define HT_LEVEL_ERROR          "\033[1;31m"
#define HT_LEVEL_WARNING        "\033[1;33m"
#define HT_LEVEL_INFO           "\033[0;37m"
#define HT_LEVEL_MSG            "\033[1;37m"
#endif // HT_WINDOWS

#define	HT_LOG_LEVEL_FATAL      0
#define	HT_LOG_LEVEL_ERROR      1
#define	HT_LOG_LEVEL_WARNING    2
#define	HT_LOG_LEVEL_INFO       3
#define	HT_LOG_LEVEL_MSG        4

#if defined(HT_DEBUG) && !defined(HT_LOG_LEVEL)
#	define HT_LOG_LEVEL         4
#else
#	define HT_LOG_LEVEL         2
#endif // HT_DEBUG

#if HT_LOG_LEVEL_FATAL <= HT_LOG_LEVEL
#define HT_FATAL(format, ...)   ht::utils::Log(HT_LEVEL_FATAL, true, format, __VA_ARGS__)
#define _HT_FATAL(format, ...)  ht::utils::Log(HT_LEVEL_FATAL, false, format, __VA_ARGS__)
#else
#define HT_FATAL(format, ...)
#define _HT_FATAL(format, ...)
#endif // HT_LOG_LEVEL_FATAL

#if HT_LOG_LEVEL_ERROR <= HT_LOG_LEVEL
#define HT_ERROR(format, ...)   ht::utils::Log(HT_LEVEL_ERROR, true, format, __VA_ARGS__)
#define _HT_ERROR(format, ...)  ht::utils::Log(HT_LEVEL_ERROR, false, format, __VA_ARGS__)
#else
#define HT_ERROR(format, ...)
#define _HT_ERROR(format, ...)
#endif // HT_LOG_LEVEL_ERROR

#if HT_LOG_LEVEL_WARNING <= HT_LOG_LEVEL
#define HT_WARN(format, ...)   ht::utils::Log(HT_LEVEL_WARNING, true, format, __VA_ARGS__)
#define _HT_WARN(format, ...)  ht::utils::Log(HT_LEVEL_WARNING, false, format, __VA_ARGS__)
#else
#define HT_WARN(format, ...)
#define _HT_WARN(format, ...)
#endif // HT_LOG_LEVEL_WARNING

#if HT_LOG_LEVEL_INFO <= HT_LOG_LEVEL
#define HT_INFO(format, ...)   ht::utils::Log(HT_LEVEL_INFO, true, format, __VA_ARGS__)
#define _HT_INFO(format, ...)  ht::utils::Log(HT_LEVEL_INFO, false, format, __VA_ARGS__)
#else
#define HT_INFO(format, ...)
#define _HT_INFO(format, ...)
#endif // HT_LOG_LEVEL_INFO

#if HT_LOG_LEVEL_MSG <= HT_LOG_LEVEL
#define HT_MSG(format, ...)   ht::utils::Log(HT_LEVEL_MSG, true, format, __VA_ARGS__)
#define _HT_MSG(format, ...)  ht::utils::Log(HT_LEVEL_MSG, false, format, __VA_ARGS__)
#else
#define HT_MSG(format, ...)
#define _HT_MSG(format, ...)
#endif // HT_LOG_LEVEL_MSG

#ifdef HT_DEBUG
#define HT_ASSERT(condition, statement)                          \
		if(!(condition)) {                                       \
			HT_FATAL("%s", "*******************");               \
			HT_FATAL("%s", "ASSERTION FAILED");                  \
			HT_FATAL("Condition: %s", #condition);               \
			HT_FATAL("%s", statement);                           \
			HT_FATAL("File: %s, line: %d", __FILE__, __LINE__);  \
			HT_FATAL("%s", "*******************");               \
			int *a = nullptr;                                    \
			*a = 1;                                              \
		}
#else
#define HT_ASSERT(condition, statement)
#endif // HT_DEBUG

#ifdef HT_DEBUG
#	if defined(HT_OPENGL)
#		define GL(func) func; ht::utils::GLCallLog(#func, __FILE__, __LINE__)
#	elif defined(HT_DIRECTX)
#		define DX(func)	ht::utils::DXCall(func, #func, __FILE__, __LINE__)
#	endif
#else
#define GL(x) x
#define DX(x) x
#endif // HT_DEBUG

namespace ht { namespace utils {
#if defined(HT_WINDOWS)
	template<typename First, typename ... Args>
	void Log(unsigned int color, bool newline, First arg, Args... message) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
		printf(arg, std::forward<Args>(message)...);
		if (newline) printf("\n");
	}
#elif defined(HT_LINUX)
	template<typename First, typename ... Args>
	void Log(const char* color, bool newline, First arg, Args... message) {
		printf((std::string(color) + arg).c_str(), std::forward<Args>(message)...);
		if (newline) printf("\n");
}
#endif // HT_WINDOWS

#ifdef HT_OPENGL
	inline static void GLCallLog(const char* funcName, const char* file, u32 line) {
		static std::map<int, const char*> glErrors = {
			{ 0x0500, "GL_INVALID_ENUM" },
			{ 0x0501, "GL_INVALID_VALUE" },
			{ 0x0502, "GL_INVALID_OPERATION" },
			{ 0x0503, "GL_STACK_OVERFLOW" },
			{ 0x0504, "GL_STACK_UNDERFLOW" },
			{ 0x0505, "GL_OUT_OF_MEMORY" },
			{ 0x0506, "GL_INVALID_FRAMEBUFFER_OPERATION" },
			{ 0x0507, "GL_CONTEXT_LOST" },
			{ 0x8031, "GL_TABLE_TOO_LARGE" },
		};

		u32 error = 0;
		while (error = glGetError()) {
			HT_FATAL("[GL] Error %s, calling %s in %s:%u", glErrors[error], funcName, file, line);
			int* a = nullptr;
			*a = 1;
		}
	}
#elif defined(HT_DIRECTX)
	inline static void DXCall(HRESULT result, const char* funcName, const char* file, u32 line) {
		static std::map<int, const char*> dxErrors = {
			{ D3D11_ERROR_DEFERRED_CONTEXT_MAP_WITHOUT_INITIAL_DISCARD,  "D3D11_ERROR_DEFERRED_CONTEXT_MAP_WITHOUT_INITIAL_DISCARD" },
			{ D3D11_ERROR_TOO_MANY_UNIQUE_STATE_OBJECTS,                 "D3D11_ERROR_TOO_MANY_UNIQUE_STATE_OBJECTS" },
			{ D3D11_ERROR_TOO_MANY_UNIQUE_VIEW_OBJECTS,                  "D3D11_ERROR_TOO_MANY_UNIQUE_VIEW_OBJECTS" },
			{ DXGI_ERROR_WAS_STILL_DRAWING,                              "DXGI_ERROR_WAS_STILL_DRAWING" },
			{ D3D11_ERROR_FILE_NOT_FOUND,                                "D3D11_ERROR_FILE_NOT_FOUND" },
			{ DXGI_ERROR_INVALID_CALL,                                   "DXGI_ERROR_INVALID_CALL" },
			{ E_OUTOFMEMORY,                                             "E_OUTOFMEMORY" },
			{ E_INVALIDARG,                                              "E_INVALIDARG" },
			{ E_NOTIMPL,                                                 "E_NOTIMPL" },
			{ S_FALSE,                                                   "S_FALSE" },
			{ E_FAIL,                                                    "E_FAIL" },
		};

		if (result != S_OK) {
			HT_FATAL("[DX] Error %s, calling %s in %s:%u", dxErrors[result], funcName, file, line);
			int* a = nullptr;
			*a = 1;
		}
	}
#endif // HT_OPENGL

} }