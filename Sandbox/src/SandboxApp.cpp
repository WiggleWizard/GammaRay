#include <GammaRay.h>

#include "Scene/Concepts/Mesh.h"


class Sandbox : public Application
{
public:
    Sandbox() : Application()
    {
        ConceptMesh3D testEntity = NewEntity(ConceptMesh3D, "Mesh1");
    }

    virtual bool OnProcess(float deltaTimeMs)
    {
        bool pressed = Input::GetSingleton()->IsKeyPressed(GR_KEY_A);
        if(pressed)
        {
            m_shader->LoadFromFile("D:\\Projects\\GammaRay\\test.glsl");
        }

        return true;
    }
};

Application* CreateApplication()
{
    return new Sandbox();
}
