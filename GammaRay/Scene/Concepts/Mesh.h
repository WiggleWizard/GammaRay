#pragma once

#include "Servers/SceneServer.h"
#include "Scene/Components/Transform.h"


class ConceptMesh3D : public Entity
{
public:
    virtual void InitComponents() override
    {
        AddComponent<ComponentRenderTransform3D>();
        AddComponent<ComponentTransform3D>();
    }
};
