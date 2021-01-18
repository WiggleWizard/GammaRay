#pragma once

#include "Core/Layer.h"

#include <entt/entt.hpp>


class GAMMARAY_API LayerImGui : public Layer
{
    void WidgetComponentSceneLink(struct ComponentSceneLink* c);
    void WidgetComponentTransform3D(struct ComponentTransform3D* c);
    void WidgetComponentEditorCamera3DMovement(struct ComponentEditorCamera3DMovement* c);

public:
    LayerImGui();
    ~LayerImGui();

    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnProcess() override;
    virtual void OnImGuiRender() override;

    virtual void Begin();
    virtual void End();

    void RegisterComponentWidgetRenderFunc(entt::id_type id, std::function<void(entt::registry& reg, entt::entity e)> cb)
    {
        m_inspectorWidgetRenderFuncs[id] = cb;
    }

private:
    float m_time = 0.f;
    bool m_isControllingCamera = false;
    entt::entity m_entitySelected = entt::null;
    std::unordered_map<entt::id_type, std::function<void(entt::registry& reg, entt::entity e)>> m_inspectorWidgetRenderFuncs;
};
