#pragma once

#include "Rendering/Viewport.h"

class GameViewport : public Viewport
{
    DECLARE_CLASS(GameViewport, Viewport)

public:
    GameViewport(Dg::RefCntAutoPtr<Dg::ISwapChain>& swapChain, Dg::RefCntAutoPtr<Dg::IRenderDevice>& renderDevice);

    void PreProcess() override;

protected:
    void OnInputEvent(const ObjectPtr<InputEvent> inputEvent) override;

    bool holdingLeftMouse = false;
    Dg::int2 mouseMotion = { 0, 0 };

    float camPitch = 0.0f;  // X rotation
    float camYaw = 0.0f;    // Y rotation
};
