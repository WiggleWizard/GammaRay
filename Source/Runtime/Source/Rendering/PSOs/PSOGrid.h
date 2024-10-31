#pragma once

#include "PSO3D.h"

class PSOGrid : public PSO3D
{
    DECLARE_CLASS(PSOGrid, PSO3D)

public:
    struct PSOConstants : PSO3D::PSOConstants
    {
        Dg::float3 cameraPosition;
    };
    
public:
    std::vector<Dg::LayoutElement> GetLayoutElements() override;

protected:
    virtual void ModifyPSOCreationInfo(Dg::GraphicsPipelineStateCreateInfo& creationInfo) override;
    
    size_t GetConstantBufferSizeVS() override { return sizeof (PSOConstants); }
    //size_t GetConstantBufferSizePS() override { return sizeof (PSOConstantsGrid); }
    
    virtual String GetShaderSourceVertex() override;
    virtual String GetShaderSourcePixel() override;
};
