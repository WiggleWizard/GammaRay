#pragma once

#include <RefCntAutoPtr.hpp>

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
    UUID uuid;
    Dg::Vector2<uint32> prevWindowSize;
    ObjectPtr<RenderTarget> viewport = nullptr;
};
