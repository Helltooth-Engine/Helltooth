#ifdef HT_DIRECTX
#include <d3d11.h>
#include <d3d.h>
#include <d3dcompiler.h>

#include "core/Window.hpp"

#define HT_DXDEVICE   ht::core::Window::GetWindow()->GetDevice()
#define HT_DXCONTEXT  ht::core::Window::GetWindow()->GetDeviceContext()

#endif // HT_DIRECTX