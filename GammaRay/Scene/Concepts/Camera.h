#pragma once

#include "Servers/SceneServer.h"
#include "Scene/Components/Transform.h"
#include "Scene/Components/Camera.h"
#include "Scene/Components/Gameplay/CameraMovement.h"


class ConceptCamera3D : public Entity
{
public:
    virtual void InitComponents() override
    {
        AddComponent<ComponentTransform3D>();
        AddComponent<ComponentCamera3D>();
    }
};

class ConceptEditorCamera3D : public Entity
{
public:
    virtual void InitComponents() override
    {
        AddComponent<ComponentTransform3D>();
        AddComponent<ComponentCamera3D>();
        AddComponent<ComponentEditorCamera3DMovement>();
    }
};
