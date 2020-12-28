#include <GammaRay.h>

#include "Core/Debug/LayerImGui.h"
#include "Core/Input/Input.h"


class Sandbox : public Application
{
public:
    Sandbox()
    {
        PushLayer(new LayerImGui());
    }

    virtual bool OnProcess(float deltaTimeMs)
    {
        bool pressed = Input::GetSingleton()->IsKeyPressed(70);
        if(pressed)
        {
            GR_CLIENT_TRACE("Hello world");
        }

        return true;
    }
};

Application* CreateApplication()
{
    return new Sandbox();
}
