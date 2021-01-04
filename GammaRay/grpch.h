#pragma once

// Algorithm
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

// Structure
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <unordered_set>

// Internal algorithm
#include "Core/OS/Memory.h"
#include "Core/Core.h"
#include "Core/Debug/Log.h"

// Internal structures
#include "Core/Typedefs.h"
#include "Core/Color.h"
#include "Core/Math/MathDefs.h"
#include "Core/Math/Vector2.h"

// Internal frequently used objects
#include "Core/Object/Object.h"

// Thirdparty frequently used
#include <glm/glm.hpp>

#ifdef GR_PLATFORM_WINDOWS
    #include <Windows.h>
#endif
