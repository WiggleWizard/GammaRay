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

void ResourceMaterialInstance::WriteGeneralVS(Dg::RefCntAutoPtr<Dg::IDeviceContext> deviceContext,
    const Dg::float4x4& cameraViewMatrix, const Dg::float4x4& cameraProjectionMatrix, const Dg::float4x4& matrix)
{
    auto worldViewProj = matrix * cameraViewMatrix * cameraProjectionMatrix;
    
}

void ResourceMaterialInstance::Commit()
{
    masterMaterial->Commit();
}
