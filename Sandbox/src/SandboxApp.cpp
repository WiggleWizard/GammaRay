#include <GammaRay.h>


class Sandbox : public Application
{
public:
    Sandbox()
    {
    }

    virtual bool OnProcess(float deltaTimeMs)
    {
        bool pressed = Input::GetSingleton()->IsKeyPressed(GR_KEY_A);
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
