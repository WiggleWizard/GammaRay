#pragma once

#include "Viewport.h"

class WindowViewport : public Viewport
{
public:
    WindowViewport();
    WindowViewport(Dg::RefCntAutoPtr<Dg::ISwapChain> swapChain, Dg::RefCntAutoPtr<Dg::IRenderDevice> renderDevice);
};
