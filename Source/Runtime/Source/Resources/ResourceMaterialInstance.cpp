#include "ResourceMaterialInstance.h"

#include "Rendering/PipelineShaderObject.h"

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

bool ResourceMaterialInstance::IsFromMasterMaterial(const Res<ResourceMasterMaterial>& other) const
{
    return masterMaterial == other;
}

bool ResourceMaterialInstance::IsPSOInitialized()
{
    if (masterMaterial)
    {
        return masterMaterial->IsPSOInitialized();
    }
    return false;
}

void ResourceMaterialInstance::InitializePSO(Dg::RefCntAutoPtr<Dg::IRenderDevice> renderDevice, Dg::RefCntAutoPtr<Dg::ISwapChain> swapChain)
{
    if (masterMaterial)
    {
        masterMaterial->InitializePSO(renderDevice, swapChain);
    }
}

void ResourceMaterialInstance::Bind(Dg::RefCntAutoPtr<Dg::IDeviceContext> renderDevice)
{
    if (masterMaterial)
    {
        masterMaterial->Bind(renderDevice);
    }
}

void ResourceMaterialInstance::WriteGeneralVS(Dg::RefCntAutoPtr<Dg::IDeviceContext> deviceContext,
                                              const Dg::float4x4& cameraViewMatrix, const Dg::float4x4& cameraProjectionMatrix, const Dg::float4x4& matrix)
{
    if (masterMaterial)
    {
        masterMaterial->WriteGeneralVS(deviceContext, cameraViewMatrix, cameraProjectionMatrix, matrix);
    }
}

void ResourceMaterialInstance::Commit(Dg::RefCntAutoPtr<Dg::IDeviceContext> deviceContext)
{
    if (masterMaterial)
    {
        masterMaterial->Commit(deviceContext);
    }
}
