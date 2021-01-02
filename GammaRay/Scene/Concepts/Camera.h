#pragma once

#include "Servers/SceneServer.h"
#include "Scene/Components/Transform.h"
#include "Scene/Components/Camera.h"


class ConceptCamera3D : public Entity
{
public:
    virtual void InitComponents() override
    {
        AddComponent<ComponentTransform3D>();
        AddComponent<ComponentCamera3D>();
    }
};
