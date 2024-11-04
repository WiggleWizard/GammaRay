#include "ResourceMasterMaterial3D.h"

#include "Rendering/PipelineShaderObject.h"
#include "Rendering/PSOs/PSO3D.h"

void ResourceMasterMaterial3D::WriteGeneralVS(Dg::RefCntAutoPtr<Dg::IDeviceContext> deviceContext,
                                              const Dg::float4x4& cameraViewMatrix, const Dg::float4x4& cameraProjectionMatrix, const Dg::float4x4& matrix)
{
    auto psoConstants = pso->WriteVS<PSO3D::PSOConstants>(deviceContext);
    psoConstants->worldViewProj = matrix * cameraViewMatrix.Inverse() * cameraProjectionMatrix;
    psoConstants->world = matrix;
}

void ResourceMasterMaterial3D::Commit(Dg::RefCntAutoPtr<Dg::IDeviceContext> deviceContext)
{
    pso->Commit(deviceContext);
}
