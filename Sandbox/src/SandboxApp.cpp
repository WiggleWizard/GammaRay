#include <GammaRay.h>

class Sandbox : public Application
{
public:

    void Step(float DeltaTimeMS) override
    {
        
    };
};

Application* CreateApplication()
{
    return new Sandbox();
}
