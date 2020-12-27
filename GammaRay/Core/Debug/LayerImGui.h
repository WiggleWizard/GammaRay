#pragma once

#include "Core/Layer.h"

#include "Core/Event/EventMouse.h"


class GAMMARAY_API LayerImGui : public Layer
{
public:
    LayerImGui();
    ~LayerImGui();

    virtual void OnAttach();
    virtual void OnDetach();
    virtual void OnProcess() override;
    virtual void OnEvent(Event& event) override;

    bool OnMouseMove(EventMouseMoved& event);
    bool OnMousePressed(EventMousePressed& event);
    bool OnMouseRelease(EventMouseRelease& event);
    bool OnMouseScrolled(EventMouseScrolled& event);

private:
    float m_time = 0.f;
};
