#pragma once

#include "RenderTarget.h"

class Viewport : public RenderTarget
{
public:
    Viewport();
    Viewport(Dg::RefCntAutoPtr<Dg::ISwapChain>& swapChain, Dg::RefCntAutoPtr<Dg::IRenderDevice>& renderDevice);
};
