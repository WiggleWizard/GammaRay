#pragma once

#include <Graphics/GraphicsTools/interface/MapHelper.hpp>

template<class ConstantsType>
class PSOConstantsImpl
{
public:
    Dg::MapHelper<ConstantsType> Write(Dg::RefCntAutoPtr<Dg::IDeviceContext> deviceContext)
    {
        return Dg::MapHelper<ConstantsType>(deviceContext, constants, Dg::MAP_WRITE, Dg::MAP_FLAG_DISCARD);
    }
    
protected:
    ConstantsType constants;
};
