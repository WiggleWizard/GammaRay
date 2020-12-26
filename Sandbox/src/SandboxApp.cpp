#include <GammaRay.h>

class Sandbox : public Application
{
public:
    virtual bool OnProcess(float deltaTimeMs)
    {
        return true;
    }
};

Application* CreateApplication()
{
    return new Sandbox();
}
