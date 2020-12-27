#pragma once

#include "Core/Layer.h"


class GAMMARAY_API LayerImGui : public Layer
{
public:
    LayerImGui();
    ~LayerImGui();

    virtual void OnAttach();
    virtual void OnDetach();
    virtual void OnProcess() override;
    virtual void OnEvent(Event& event) override;

private:
    float m_time = 0.f;
};
