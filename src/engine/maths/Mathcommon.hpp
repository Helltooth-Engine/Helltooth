#pragma once

#ifdef HT_WINDOWS
#include <mmintrin.h>
#else
#error Other platforms not supported.
#endif

#define M_PI 3.14159265358979323846264338327950288419716939937510

#define ToRadians(x) x * 0.01745329251
#define ToDegrees(x) x * 57.2957795131
