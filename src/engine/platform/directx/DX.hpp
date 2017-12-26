#ifdef HT_DIRECTX
#include <d3d11.h>
#include <d3d.h>
#include <d3dcompiler.h>

#include "core/Window.hpp"

#define DIRECTX_DEVICE ht::core::Window::GetWindow()->GetDevice()
#define DIRECTX_CONTEXT ht::core::Window::GetWindow()->GetDeviceContext()

#endif