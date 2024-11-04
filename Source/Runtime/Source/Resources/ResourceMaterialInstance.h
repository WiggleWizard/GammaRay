#pragma once

#include "Resource.h"
#include "Res.h"
#include "ResourceMasterMaterial.h"

class ResourceMaterialInstance : public Resource
{
public:
    static Res<ResourceMaterialInstance> FromMasterMaterial(Res<ResourceMasterMaterial> masterMaterial);
    
    void SetMasterMaterial(Res<ResourceMasterMaterial> masterMaterial);

    ObjectPtr<PipelineShaderObject> GetPSO()
    {
        return masterMaterial->GetPSO();
    }

    virtual bool IsPSOInitialized();

    virtual void InitializePSO(Dg::RefCntAutoPtr<Dg::IRenderDevice> renderDevice, Dg::RefCntAutoPtr<Dg::ISwapChain> swapChain);

    virtual void WriteGeneralVS(Dg::RefCntAutoPtr<Dg::IDeviceContext> deviceContext, const Dg::float4x4& cameraViewMatrix,
        const Dg::float4x4& cameraProjectionMatrix, const Dg::float4x4& matrix);

    virtual void Commit(Dg::RefCntAutoPtr<Dg::IDeviceContext> deviceContext);

protected:
    Res<ResourceMasterMaterial> masterMaterial;
};
