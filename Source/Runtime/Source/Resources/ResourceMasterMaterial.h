#pragma once

#include "Res.h"
#include "Resource.h"

class PipelineShaderObject;

// A Master Material provides a "template" for a material instance to tie shader/PSO with data such as textures, floats, matrices, etc.
// When it comes to the data, a Master Material simply provides the defaults. A ResourceMaterialInstance must be made to modify this
// data per instance.
class ResourceMasterMaterial : public Resource
{
public:
    virtual ObjectPtr<PipelineShaderObject> GetPSO() { return pso; }

    virtual bool IsPSOInitialized();

    virtual void InitializePSO(Dg::RefCntAutoPtr<Dg::IRenderDevice> renderDevice, Dg::RefCntAutoPtr<Dg::ISwapChain> swapChain);

    void Bind(Dg::RefCntAutoPtr<Dg::IDeviceContext> renderDevice);
    
    virtual void WriteGeneralVS(Dg::RefCntAutoPtr<Dg::IDeviceContext> deviceContext, const Dg::float4x4& cameraViewMatrix,
        const Dg::float4x4& cameraProjectionMatrix, const Dg::float4x4& matrix) {}
    
    virtual void Commit(Dg::RefCntAutoPtr<Dg::IDeviceContext> deviceContext) {}

protected:
    ObjectPtr<PipelineShaderObject> pso = nullptr;
};
