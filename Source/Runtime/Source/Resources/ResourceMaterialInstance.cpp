#include "ResourceMaterialInstance.h"

Res<ResourceMaterialInstance> ResourceMaterialInstance::FromMasterMaterial(Res<ResourceMasterMaterial> masterMaterial)
{
    Res resourceMaterialInstance(new ResourceMaterialInstance());

    resourceMaterialInstance->SetMasterMaterial(masterMaterial);

    return resourceMaterialInstance;
}

void ResourceMaterialInstance::SetMasterMaterial(Res<ResourceMasterMaterial> inMasterMaterial)
{
    masterMaterial = inMasterMaterial;
}

void ResourceMaterialInstance::Commit()
{
    masterMaterial->Commit();
}
