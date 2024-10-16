#pragma once

#include <entt/fwd.hpp>

class World : public Object
{
public:
    World();

    SharedPtr<entt::registry> GetRegistry() { return registry; }
    
protected:
    SharedPtr<entt::registry> registry = nullptr;
};
