#include "ResourceMasterMaterialGrid.h"

#include "Rendering/PSOs/PSOGrid.h"

ResourceMasterMaterialGrid::ResourceMasterMaterialGrid()
{
    pso = NewObject<PSOGrid>();
}

void ResourceMasterMaterialGrid::WriteGeneralVS(Dg::RefCntAutoPtr<Dg::IDeviceContext> deviceContext,
    const Dg::float4x4& cameraViewMatrix, const Dg::float4x4& cameraProjectionMatrix, const Dg::float4x4& matrix)
{
    //ResourceMasterMaterial3D::WriteGeneralVS(deviceContext, cameraViewMatrix, cameraProjectionMatrix, matrix);
    
    auto psoConstants = pso->WriteVS<PSOGrid::PSOConstants>(deviceContext);
    psoConstants->worldViewProj = matrix * cameraViewMatrix.Inverse() * cameraProjectionMatrix;
    psoConstants->world = matrix;
    psoConstants->cameraPosition = GetPositionFromMatrix(cameraViewMatrix);
}
