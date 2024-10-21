#pragma once

#include "Component.h"

#include <BasicMath.hpp>

namespace Dg = Diligent;

class CameraComponent : public Component
{
public:
    Dg::float4x4 frustum;
    
    float fov = 70.f;
    float zNear = 0.01f;
    float zFar = 100.f;

    void ComputeProjectionMatrix(float aspectRatio)
    {
        frustum = Dg::float4x4::Projection(fov, aspectRatio, zNear, zFar, false);
    }
};
