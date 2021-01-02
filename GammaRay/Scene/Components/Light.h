#pragma once

#include "Core/Color.h"

#include <glm/glm.hpp>


struct ComponentLight3D
{
    Color color;
    float strength;
    // TODO: Type (Directional, point, etc)
    glm::vec3 direction;
};
