#pragma once

#include "PSO3D.h"
#include "Rendering/PSOConstantsImpl.h"

struct PSOConstantsGrid : PSOConstants3D {};

class PSOGrid : public PSO3D, public PSOConstantsImpl<PSOConstantsGrid>
{
public:
    std::vector<Dg::LayoutElement> GetLayoutElements() override;

protected:
    virtual void SetupConstantsBuffer(Dg::RefCntAutoPtr<Dg::IRenderDevice> renderDevice) override;

    virtual String GetShaderSourceVertex() override;
    virtual String GetShaderSourcePixel() override;
};
