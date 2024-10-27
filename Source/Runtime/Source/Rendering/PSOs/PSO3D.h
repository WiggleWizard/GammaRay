#pragma once

#include "Rendering/PipelineShaderObject.h"

class PSO3D : public PipelineShaderObject
{
public:
    struct PSOConstants
    {
        Dg::float4x4 worldViewProj;
        Dg::float4x4 world;
    };
    
public:
    virtual std::vector<Dg::LayoutElement> GetLayoutElements() override;

    virtual Dg::RefCntAutoPtr<Dg::IBuffer> GetConstantBufferVS() override;

protected:
    size_t GetConstantBufferSizeVS() override { return sizeof(PSOConstants); }
    size_t GetConstantBufferSizePS() override { return 0; }
    
    virtual String GetShaderSourceVertex() override;
    virtual String GetShaderSourcePixel() override;
};
