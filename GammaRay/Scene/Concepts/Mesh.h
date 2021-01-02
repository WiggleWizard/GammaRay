#pragma once

#include "Servers/SceneServer.h"
#include "Scene/Components/Transform.h"


class ConceptMesh3D : public Entity
{
public:
    virtual void InitComponents() override
    {
        AddComponent<ComponentRenderTransform3D>();

        ComponentTransform3D& transform3D = AddComponent<ComponentTransform3D>();
        transform3D.position = glm::vec3(0.0f, 0.0f, -3.0f);
    }
};
