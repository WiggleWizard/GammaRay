#pragma once

#include "Resource.h"
#include "Res.h"
#include "ResourceMasterMaterial.h"

class ResourceMaterialInstance : public Resource
{
public:

protected:
    Res<ResourceMasterMaterial> masterMaterial;
};
