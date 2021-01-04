#pragma once

#include <entt/entt.hpp>

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

    void RegisterForOnUpdate(std::function<void()> cb)
    {
        m_updateCallbacks.push_back(cb);
    }

    void OnUpdate()
    {
        for(const auto& cb : m_updateCallbacks)
        {
            cb();
        }
    }

    SceneServer()
    {
        m_singleton = this;
    }

private:
    static SceneServer* m_singleton;
    entt::registry m_registry;

    std::vector<std::function<void()>> m_updateCallbacks;
};

