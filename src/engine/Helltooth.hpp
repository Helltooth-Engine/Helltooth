#pragma once
#if !(defined(HT_OPENGL) || defined(HT_DIRECTX))
#error ("No Graphics API defined!")
#endif

#include "platform/opengl/GL.hpp"
#include "core/Window.hpp"
