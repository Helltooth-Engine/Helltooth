#pragma once
#if !(defined(HT_OPENGL) || defined(HT_DIRECTX))
#error ("No Graphics API defined!")
#endif

#include "core/Window.hpp"

#include "utils/Log.hpp"