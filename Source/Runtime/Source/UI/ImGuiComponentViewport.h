#pragma once

#include "ImGuiComponent.h"

#include <BasicMath.hpp>

class Viewport;

namespace Diligent
{
    struct IRenderDevice;
    struct ISwapChain;
    struct ITexture;
    struct ITextureView;
}
namespace Dg = Diligent;

class ImGuiComponentViewport : public ImGuiComponent
{
public:
    ImGuiComponentViewport(ObjectPtr<Viewport> viewport);
    
    virtual void Draw() override;
    
    void ImGuiWindowResized(uint32 width, uint32 height);

    virtual void ProcessUI() {}

private:
    uint32 prevSizeX = 0;
    uint32 prevSizeY = 0;
    ObjectPtr<Viewport> viewport = nullptr;
};
