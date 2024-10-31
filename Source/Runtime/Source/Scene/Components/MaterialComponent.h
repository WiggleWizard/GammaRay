#pragma once

#include "Component.h"
#include "Resources/Res.h"
#include "Resources/ResourceMaterialInstance.h"

class PipelineShaderObject;

class MaterialComponent : public Component
{
    Res<ResourceMaterialInstance> GetMaterial()
    {
        return material;
    }

    void SetMaterial(Res<ResourceMaterialInstance> inMaterial)
    {
        material = inMaterial;
    }
    
public:
    Res<ResourceMaterialInstance> material;
};
