#include "World.h"

#include <entt/entt.hpp>

World::World()
{
    registry = MakeShared<entt::registry>();
}
