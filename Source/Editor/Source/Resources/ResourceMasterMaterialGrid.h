#pragma once

#include "Resources/ResourceMasterMaterial3D.h"

class ResourceMasterMaterialGrid : public ResourceMasterMaterial3D
{
public:
    ResourceMasterMaterialGrid();

    void WriteGeneralVS(Dg::RefCntAutoPtr<Dg::IDeviceContext> deviceContext, const Dg::float4x4& cameraViewMatrix,
                        const Dg::float4x4& cameraProjectionMatrix, const Dg::float4x4& matrix) override;
};
