#pragma once

#include "Component.h"

#include <BasicMath.hpp>

class TransformComponent : public Component
{
public:
    Diligent::Matrix4x4<float> matrix;
};