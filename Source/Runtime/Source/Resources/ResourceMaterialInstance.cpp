#include "ResourceMaterialInstance.h"

Res<ResourceMaterialInstance> ResourceMaterialInstance::FromMasterMaterial(Res<ResourceMasterMaterial> masterMaterial)
{
    Res resourceMaterialInstance(new ResourceMaterialInstance());

    resourceMaterialInstance->masterMaterial = masterMaterial;

    return resourceMaterialInstance;
}

void ResourceMaterialInstance::SetMasterMaterial(Res<ResourceMasterMaterial>& inMasterMaterial)
{
    masterMaterial = inMasterMaterial;
}
