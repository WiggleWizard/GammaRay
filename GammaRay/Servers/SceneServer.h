#pragma once

#include "Scene/Components/Base.h"

#include "entt/entt.hpp"

#define NewEntity(conceptType, entityName) SceneServer::GetSingleton()->CreateEntity<conceptType>(entityName)

typedef uint32_t SceneRID;


class SceneServer
{
    friend class Entity;

public:
    static SceneServer* GetSingleton() { return m_singleton; }

    template<class T>
    T CreateEntity(const std::string& entityName, SceneRID sceneId = 0)
    {
        T newEntity = T();
        newEntity.m_rid = m_registry.create();

        // Setup entity base component
        ComponentSceneLink& baseComponent = newEntity.AddComponent<ComponentSceneLink>();
        baseComponent.entityName = entityName;
        baseComponent.sceneId = sceneId;

        // Allow custom entities to create their own components upon entity initialization
        newEntity.InitComponents();

        return newEntity;
    }

    entt::registry& GetRawRegistry() { return m_registry; }

    SceneServer()
    {
        m_singleton = this;
    }

private:
    static SceneServer* m_singleton;
    entt::registry m_registry;
};


/**
 * Simply an OOP wrapper around an entity ID
 */
class Entity
{
    friend class SceneServer;

public:
    Entity()
    {}

    /**
     * Allow direct wrapping of an entt ID.
     */
    Entity(entt::entity enttId)
        : m_rid(enttId)
    {}

    Entity(const Entity& e)
    {
        m_rid = e.m_rid;
    }

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
        return SceneServer::GetSingleton()->m_registry.emplace<T>(m_rid);
    }

    template<typename T>
    void RemoveComponent()
    {
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
