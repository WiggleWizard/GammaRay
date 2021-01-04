#pragma once

#include "Servers/SceneServer.h"
#include "Scene/Components/Base.h"

#include <entt/entt.hpp>


/**
 * Simply an OOP wrapper around an entity ID
 */
class Entity
{
    friend class SceneServer;

public:
    Entity()
        : m_rid((entt::entity)0)
    {}

    /**
     * Allow direct wrapping of an entt ID.
     */
    Entity(entt::entity enttId)
        : m_rid(enttId)
    {}

    Entity(const Entity& e)
        : m_rid(e.m_rid)
    {}

    virtual void InitComponents() {};

    const std::string& GetName()
    {
        ComponentSceneLink& component = GetComponent<ComponentSceneLink>();
        return component.entityName;
    }

    template<typename T>
    bool HasComponent()
    {
        return SceneServer::GetSingleton()->m_registry.has<T>(m_rid);
    }

    template<typename T>
    T& AddComponent()
    {
        T& component = SceneServer::GetSingleton()->m_registry.emplace<T>(m_rid);
        component.owner = (Entity)m_rid;
        component.OnInit();
        return component;
    }

    template<>
    ComponentSceneLink& AddComponent()
    {
        ComponentSceneLink& component = SceneServer::GetSingleton()->m_registry.emplace<ComponentSceneLink>(m_rid);
        return component;
    }

    template<typename T>
    void RemoveComponent()
    {
        // TODO: Also reset the component's owner
        SceneServer::GetSingleton()->m_registry.remove<T>(m_rid);
    }

    template<typename T>
    T& GetComponent()
    {
        return SceneServer::GetSingleton()->m_registry.get<T>(m_rid);
    }

    void Destroy()
    {
        SceneServer::GetSingleton()->m_registry.destroy(m_rid);
    }

    bool operator==(const Entity& other) const
    {
        return m_rid == other.m_rid;
    }

    bool operator!=(const Entity& other) const
    {
        return !(*this == other);
    }

private:
    entt::entity m_rid;
};
