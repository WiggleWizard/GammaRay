#pragma once

#include "Core/Layer.h"


class GAMMARAY_API LayerImGui : public Layer
{
public:
    LayerImGui();
    ~LayerImGui();

    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnProcess() override;
    virtual void OnImGuiRender() override;

    virtual void Begin();
    virtual void End();


private:
    float m_time = 0.f;
};
