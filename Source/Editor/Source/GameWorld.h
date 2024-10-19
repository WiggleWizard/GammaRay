#pragma once

#include "Engine/World.h"

class TransformComponent;

class GameWorld : public World
{
public:
    GameWorld();

    void Initialize();

    void Process();

private:
    TransformComponent* xformComponent = nullptr;

    float rotation = 0.f;
};
