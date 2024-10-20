#pragma once

#include "ImGuiComponent.h"

#include <BasicMath.hpp>

class RenderTarget;

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
    ImGuiComponentViewport(ObjectPtr<RenderTarget> viewport);
    
    virtual void Draw() override;
    
    void OnResized(uint32 width, uint32 height);

private:
    uint32 prevSizeX = 0;
    uint32 prevSizeY = 0;
    ObjectPtr<RenderTarget> viewport = nullptr;
};
