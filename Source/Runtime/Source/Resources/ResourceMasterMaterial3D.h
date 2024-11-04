#pragma once

#include "ResourceMasterMaterial.h"

class ResourceMasterMaterial3D : public ResourceMasterMaterial
{
public:
    void WriteGeneralVS(Dg::RefCntAutoPtr<Dg::IDeviceContext> deviceContext, const Dg::float4x4& cameraViewMatrix,
                        const Dg::float4x4& cameraProjectionMatrix, const Dg::float4x4& matrix) override;

    void Commit(Dg::RefCntAutoPtr<Dg::IDeviceContext> deviceContext) override;
};
