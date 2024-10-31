#pragma once

#include "Resource.h"
#include "Res.h"
#include "ResourceMasterMaterial.h"

class ResourceMaterialInstance : public Resource
{
public:
    static Res<ResourceMaterialInstance> FromMasterMaterial(Res<ResourceMasterMaterial> masterMaterial);
    
    void SetMasterMaterial(Res<ResourceMasterMaterial>& masterMaterial);

protected:
    Res<ResourceMasterMaterial> masterMaterial;
};
