#pragma once
#if !(defined(HT_OPENGL) || defined(HT_DIRECTX))
#error ("No Graphics API defined!")
#endif

#include "core/Window.hpp"
#include "core/Asset.hpp"
#include "core/input/Event.hpp"
#include "core/input/EventDispatcher.hpp"
#include "core/input/EventListener.hpp"
#include "core/input/Keys.hpp"

#include "graphics/buffers/VertexBuffer.hpp"
#include "graphics/buffers/UniformBuffer.hpp"
#include "graphics/buffers/IndexBuffer.hpp"
#include "graphics/camera/Camera.hpp"
#include "graphics/camera/FPSCamera.hpp"
#include "graphics/Context.hpp"
#include "graphics/Enums.hpp"
#include "graphics/Entity.hpp"

#include "maths/Mathcommon.hpp"
#include "maths/Vector2.hpp"
#include "maths/Vector3.hpp"
#include "maths/Vector4.hpp"
#include "maths/Matrix4.hpp"

#include "utils/Log.hpp"
#include "utils/String.hpp"
#include "utils/Vfs.hpp"
#include "utils/Timer.hpp"
#include "utils/FileUtils.hpp"