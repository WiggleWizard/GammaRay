#pragma once

#include "Core/Object/Component.h"

#include "Scene/Components/Transform.h"

#include <glm/glm.hpp>
#include <glm/ext.hpp>


struct ComponentCamera2D
{

};

struct ComponentCamera3D : public Component
{
    // Yaw, pitch & roll embedded in ComponentTransform3D::rotation

    glm::vec3 forward = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 up      = glm::vec3(0.0f, 1.0f,  0.0f);
    glm::vec3 right   = glm::vec3(1.0f, 0.0f,  0.0f);

    float fov = 90.f;
    float nearClip = 0.1f;
    float farClip  = 100.f;

    glm::mat4 GetViewMatrix()
    {
        // Position is stored in the transform component so fetch that
        ComponentTransform3D& transform3D = owner.GetComponent<ComponentTransform3D>();
        return glm::lookAt(transform3D.position, transform3D.position + this->forward, this->up);
    }
};
