#pragma once
#include <Windows.h>
#include <utility>

#define HT_LEVEL_FATAL			0x04
#define HT_LEVEL_ERROR			0x0C
#define HT_LEVEL_WARNING		0x0E
#define HT_LEVEL_DEBUG			0x0F
#define HT_LEVEL_MSG			0x07

#define	HT_LOG_LEVEL_FATAL		0
#define	HT_LOG_LEVEL_ERROR		1
#define	HT_LOG_LEVEL_WARNING	2
#define	HT_LOG_LEVEL_DEBUG		3 
#define	HT_LOG_LEVEL_MSG		4	

#ifdef HT_DEBUG && !defined(HT_LOG_LEVEL)
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

#if HT_LOG_LEVEL_DEBUG <= HT_LOG_LEVEL
#define HT_DEBUG(format, ...) ht::utils::Log(HT_LEVEL_DEBUG, true, format, __VA_ARGS__)
#define _HT_DEBUG(format, ...) ht::utils::Log(HT_LEVEL_DEBUG, false, format, __VA_ARGS__)
#else
#define HT_DEBUG(format, ...)
#define _HT_DEBUG(format, ...)
#endif

#if HT_LOG_LEVEL_MSG <= HT_LOG_LEVEL
#define HT_MSG(format, ...) ht::utils::Log(HT_LEVEL_MSG, true, format, __VA_ARGS__)
#define _HT_MSG(format, ...) ht::utils::Log(HT_LEVEL_MSG, false, format, __VA_ARGS__)
#else
#define HT_MSG(format, ...)
#define _HT_MSG(format, ...)
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
} }