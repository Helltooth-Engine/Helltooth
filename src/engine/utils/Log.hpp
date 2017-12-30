#pragma once
#include <Windows.h>
#include <utility>
#include <intrin.h>


#ifdef HT_OPENGL
#include "platform/opengl/GL.hpp"
#endif

#include "core/Internal.hpp"

#define HT_LEVEL_FATAL			0x04
#define HT_LEVEL_ERROR			0x0C
#define HT_LEVEL_WARNING		0x0E
#define HT_LEVEL_INFO			0x0F
#define HT_LEVEL_MSG			0x07

#define	HT_LOG_LEVEL_FATAL		0
#define	HT_LOG_LEVEL_ERROR		1
#define	HT_LOG_LEVEL_WARNING	2
#define	HT_LOG_LEVEL_INFO		3 
#define	HT_LOG_LEVEL_MSG		4	

#if defined(HT_DEBUG) && !defined(HT_LOG_LEVEL)
#	define HT_LOG_LEVEL 4
#else
#	define HT_LOG_LEVEL 2
#endif

#if HT_LOG_LEVEL_FATAL <= HT_LOG_LEVEL
#define HT_FATAL(format, ...) ht::utils::Log(HT_LEVEL_FATAL, true, format, __VA_ARGS__)
#define _HT_FATAL(format, ...) ht::utils::Log(HT_LEVEL_FATAL, false, format, __VA_ARGS__)
#else
#define HT_FATAL(format, ...)
#define _HT_FATAL(format, ...)
#endif

#if HT_LOG_LEVEL_ERROR <= HT_LOG_LEVEL
#define HT_ERROR(format, ...) ht::utils::Log(HT_LEVEL_ERROR, true, format, __VA_ARGS__)
#define _HT_ERROR(format, ...) ht::utils::Log(HT_LEVEL_ERROR, false, format, __VA_ARGS__)
#else
#define HT_ERROR(format, ...)
#define _HT_ERROR(format, ...)
#endif

#if HT_LOG_LEVEL_WARNING <= HT_LOG_LEVEL
#define HT_WARN(format, ...) ht::utils::Log(HT_LEVEL_WARNING, true, format, __VA_ARGS__) 
#define _HT_WARN(format, ...) ht::utils::Log(HT_LEVEL_WARNING, false, format, __VA_ARGS__) 
#else
#define HT_WARN(format, ...)
#define _HT_WARN(format, ...)
#endif

#if HT_LOG_LEVEL_INFO <= HT_LOG_LEVEL
#define HT_INFO(format, ...) ht::utils::Log(HT_LEVEL_INFO, true, format, __VA_ARGS__)
#define _HT_INFO(format, ...) ht::utils::Log(HT_LEVEL_INFO, false, format, __VA_ARGS__)
#else
#define HT_INFO(format, ...)
#define _HT_INFO(format, ...)
#endif

#if HT_LOG_LEVEL_MSG <= HT_LOG_LEVEL
#define HT_MSG(format, ...) ht::utils::Log(HT_LEVEL_MSG, true, format, __VA_ARGS__)
#define _HT_MSG(format, ...) ht::utils::Log(HT_LEVEL_MSG, false, format, __VA_ARGS__)
#else
#define HT_MSG(format, ...)
#define _HT_MSG(format, ...)
#endif
#ifdef HT_DEBUG
#define HT_ASSERT(condition, statement) if(condition)  {\
			HT_FATAL("*******************"); \
			HT_FATAL("ASSERTION FAILED"); \
			HT_FATAL("Condition: %s", #condition); \
			HT_FATAL("%s", statement); \
			HT_FATAL("File: %s, line: %d", __FILE__, __LINE__); \
			HT_FATAL("*******************"); \
			__debugbreak(); \
		}
#else
#define HT_ASSERT(condition, statement)
#endif

#ifdef HT_DEBUG
#	if defined(HT_OPENGL)
#		define GL(func) func; ht::utils::GLCallLog(#func, __FILE__, __LINE__)
#	elif defined(HT_DIRECTX)
#		define DX(func) ht::utils::DXCall(func, #func, __FILE__, __LINE__)
#	else
#		error Platform not recognized!
#	endif
#else
#define GL(x) x

#endif

namespace ht { namespace utils {
#ifdef HT_WINDOWS
	template<typename First, typename ... Args>
	void Log(unsigned int color, bool newline, First arg, Args... message) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
		printf(arg, std::forward<Args>(message)...);
		if (newline) printf("\n");
	}
#else
#	error "Log file not created for other platforms."
#endif
#ifdef HT_OPENGL
	inline static void GLCallLog(const char* funcName, const char* file, u32 line) {
		u32 error = 0;
		while (error = glGetError()) {
			HT_FATAL("[GL] Error %u, calling %s in %s:%u", error, funcName, file, line);
			__debugbreak();
		}
	}
#elif defined(HT_DIRECTX)

	inline static void DXCall(HRESULT result, const char* funcName, const char* file, u32 line) {
		if (result != S_OK) {
			HT_FATAL("[DX] Error %u, calling %s in %s:%u", result, funcName, file, line);
			__debugbreak();
		}
	}
#endif
} }