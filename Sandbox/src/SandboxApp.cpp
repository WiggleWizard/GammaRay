#include <GammaRay.h>

#include "Servers/SceneServer.h"
#include "Scene/Concepts/Mesh.h"


class Sandbox : public Application
{
    ConceptMesh3DBox testBox1, testBox2;

public:
    Sandbox() : Application()
    {
        testBox1 = NewEntity(ConceptMesh3DBox, "Mesh1");
        testBox2 = NewEntity(ConceptMesh3DBox, "Mesh2");
    }

    virtual bool OnProcess(float deltaTimeMs)
    {
        bool pressed = Input::GetSingleton()->IsKeyPressed(GR_KEY_A);
        if(pressed)
        {
            m_shader->LoadFromFile("D:\\Projects\\GammaRay\\test.glsl");
        }

        float speed = 0.04;
        float moveX = 0.f;
        if(Input::GetSingleton()->IsKeyPressed(GR_KEY_LEFT))
            moveX -= speed;
        if(Input::GetSingleton()->IsKeyPressed(GR_KEY_RIGHT))
            moveX += speed;

        float moveY = 0.f;
        if(Input::GetSingleton()->IsKeyPressed(GR_KEY_UP))
            moveY += speed;
        if(Input::GetSingleton()->IsKeyPressed(GR_KEY_DOWN))
            moveY -= speed;

        ComponentTransform3D& box1Transform = testBox2.GetComponent<ComponentTransform3D>();
        box1Transform.position.x += moveX;
        box1Transform.position.y += moveY;

        return true;
    }
};

Application* CreateApplication()
{
    return new Sandbox();
}
