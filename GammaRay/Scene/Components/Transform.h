#pragma once

#include "Core/Object/Component.h"
#include "Core/Math/Rect.h"

#include <glm/glm.hpp>
#include <glm/ext.hpp>


/**
 * Final renderer matrix
 */
struct ComponentRenderTransform3D : public Component
{
    glm::mat4 matrix;
};

struct ComponentTransform3D : public Component
{
    glm::vec3 position;
    // TODO: glm::quat rotation;
    glm::vec3 rotation;
    glm::vec3 scale;

    uint32_t flags = 0;

    _FORCE_INLINE_ bool isDirty() { return flags & 1; }
    _FORCE_INLINE_ void setDirty() { flags |= 1; }
    _FORCE_INLINE_ void resetDirty() { flags &= 0; }

};

struct ComponentTransformRect : public Component
{
    Rect2 anchors;
    Rect2i rect;
    float rotation;
    glm::vec2 scale;
};

