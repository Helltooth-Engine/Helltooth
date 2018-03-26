#pragma once

#if defined(HT_WINDOWS)
#include <intrin.h>
#elif defined(HT_LINUX)
#include <x86intrin.h>
#else
#error Other platforms not supported.
#endif

#if !defined(M_PI)
#define M_PI 3.14159265358979323846264338327950288419716939937510f
#endif

#define ToRadians(x) x * 0.01745329251f
#define ToDegrees(x) x * 57.2957795131f
