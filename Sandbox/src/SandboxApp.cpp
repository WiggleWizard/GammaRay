#include <GammaRay.h>

#include "Core/Debug/LayerImGui.h"


class Sandbox : public Application
{
public:
    Sandbox()
    {
        PushLayer(new LayerImGui());
    }

    virtual bool OnProcess(float deltaTimeMs)
    {
        return true;
    }
};

Application* CreateApplication()
{
    return new Sandbox();
}
