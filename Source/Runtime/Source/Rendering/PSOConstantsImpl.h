#pragma once

#include <Graphics/GraphicsTools/interface/MapHelper.hpp>

struct PSOConstantsVSBase {};
struct PSOConstantsPSBase {};

template<class ConstantsTypeVS, class ConstantsTypePS = PSOConstantsPSBase>
class PSOConstantsImpl
{
public:
    Dg::MapHelper<ConstantsTypeVS> WriteVS(Dg::RefCntAutoPtr<Dg::IDeviceContext> deviceContext)
    {
        return Dg::MapHelper<ConstantsTypeVS>(deviceContext, GetConstantBufferVS(), Dg::MAP_WRITE, Dg::MAP_FLAG_DISCARD);
    }
    
    Dg::MapHelper<ConstantsTypePS> WritePS(Dg::RefCntAutoPtr<Dg::IDeviceContext> deviceContext)
    {
        return Dg::MapHelper<ConstantsTypePS>(deviceContext, GetConstantBufferPS(), Dg::MAP_WRITE, Dg::MAP_FLAG_DISCARD);
    }
    
    virtual Dg::RefCntAutoPtr<Dg::IBuffer> GetConstantBufferVS() { return {}; }
    virtual Dg::RefCntAutoPtr<Dg::IBuffer> GetConstantBufferPS() { return {}; }
};
