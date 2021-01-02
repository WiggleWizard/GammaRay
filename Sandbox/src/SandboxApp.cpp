#include <GammaRay.h>

#include "Servers/SceneServer.h"
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

        float moveX = 0.f;
        if(Input::GetSingleton()->IsKeyPressed(GR_KEY_LEFT))
            moveX -= 0.01f;
        if(Input::GetSingleton()->IsKeyPressed(GR_KEY_RIGHT))
            moveX += 0.01f;

        SceneServer* sceneServer = SceneServer::GetSingleton();
        entt::registry& registry = sceneServer->GetRawRegistry();
        const auto& view = registry.view<ComponentTransform3D>();
        for(entt::entity entity : view)
        {
            ComponentTransform3D& transform3D = view.get<ComponentTransform3D>(entity);
            transform3D.position.x += moveX;
        }

        return true;
    }
};

Application* CreateApplication()
{
    return new Sandbox();
}
