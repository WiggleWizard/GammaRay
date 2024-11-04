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

    void WriteGeneralVS(Dg::RefCntAutoPtr<Dg::IDeviceContext> deviceContext, const Dg::float4x4& cameraViewMatrix,
        const Dg::float4x4& cameraProjectionMatrix, const Dg::float4x4& matrix);

    void Commit();

protected:
    Res<ResourceMasterMaterial> masterMaterial;
};
