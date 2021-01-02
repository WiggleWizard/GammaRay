#pragma once

#include "Servers/SceneServer.h"

#include "Scene/Components/Transform.h"


class ConceptCanvasItem : public Entity
{
public:
    virtual void InitComponents() override
    {
        AddComponent<ComponentTransformRect>();
    }
};
