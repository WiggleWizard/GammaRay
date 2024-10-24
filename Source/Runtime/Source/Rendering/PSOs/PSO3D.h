#pragma once

#include "Rendering/PipelineShaderObject.h"


struct PSOConstants3D
{
    Dg::float4x4 worldViewProj;
    Dg::float4x4 world;
};

class PSO3D : public PipelineShaderObject
{
public:
    virtual std::vector<Dg::LayoutElement> GetLayoutElements() override;
};
