#pragma once

#include "PSO3D.h"
#include "Rendering/PSOConstantsImpl.h"

struct PSOConstantsGrid : PSOConstants3D
{
    Dg::float3 cameraPosition;
    float gridScale;
    float lineWidth;
    Dg::float4 lineColor;
    Dg::float4 baseColor;
    int uvMode; // 0: MeshUV, 1: WorldX, 2: WorldY, 3: WorldZ
};

class PSOGrid : public PSO3D, public PSOConstantsImpl<PSOConstantsGrid, PSOConstantsGrid>
{
    DECLARE_CLASS(PSOGrid, PSO3D)
    
public:
    std::vector<Dg::LayoutElement> GetLayoutElements() override;

protected:
    size_t GetConstantBufferSizeVS() override { return sizeof (PSOConstantsGrid); }
    //size_t GetConstantBufferSizePS() override { return sizeof (PSOConstantsGrid); }
    
    virtual String GetShaderSourceVertex() override;
    virtual String GetShaderSourcePixel() override;
};
