#pragma once

#include "Component.h"
#include "Resources/Res.h"
#include "Resources/ResourceMaterialInstance.h"

class PipelineShaderObject;

class MaterialComponent : public Component
{
public:
    Res<ResourceMaterialInstance> GetMaterial() const
    {
        return material;
    }

    void SetMaterial(Res<ResourceMaterialInstance> inMaterial)
    {
        material = inMaterial;
    }
    
protected:
    Res<ResourceMaterialInstance> material;
};
