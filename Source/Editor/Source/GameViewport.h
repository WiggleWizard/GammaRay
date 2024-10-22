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

    bool controllingCamera = false;
    Dg::int2 mouseMotion = { 0, 0 };
    Dg::int2 initialDown = { 0, 0 };

    float camPitch = 0.0f;  // X rotation
    float camYaw = 0.0f;    // Y rotation
    Dg::float2 wishDir = { 0.f, 0.f };
};
