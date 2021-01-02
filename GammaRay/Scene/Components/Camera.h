#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>


struct ComponentCamera2D
{

};

struct ComponentCamera3D
{
    float nearClip, farClip;
    float fov;
};
