#pragma once

#include "Rendering/PipelineShaderObject.h"
#include "Rendering/PSOConstantsImpl.h"


struct PSOConstants3D
{
    Dg::float4x4 worldViewProj;
    Dg::float4x4 world;
};

class PSO3D : public PipelineShaderObject, public PSOConstantsImpl<PSOConstants3D>
{
public:
    virtual std::vector<Dg::LayoutElement> GetLayoutElements() override;

    virtual Dg::RefCntAutoPtr<Dg::IBuffer> GetConstantBufferVS() override;

protected:
    size_t GetConstantBufferSizeVS() override { return sizeof(PSOConstants3D); }
    size_t GetConstantBufferSizePS() override { return 0; }
    
    virtual String GetShaderSourceVertex() override;
    virtual String GetShaderSourcePixel() override;
};
