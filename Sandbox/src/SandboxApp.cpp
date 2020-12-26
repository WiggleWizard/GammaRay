#include <GammaRay.h>

class Sandbox : public Application
{
public:

};

Application* CreateApplication()
{
    return new Sandbox();
}
