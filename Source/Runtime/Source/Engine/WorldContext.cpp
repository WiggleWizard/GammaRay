#include "WorldContext.h"

void WorldContext::Process()
{
    if (IsValid(currentWorld))
    {
    }
}

void WorldContext::LoadWorld(ObjectPtr<World> world)
{
    currentWorld = world;
}
