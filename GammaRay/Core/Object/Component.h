#pragma once

#include "Entity.h"


struct Component
{
    friend class Entity;

    virtual void OnInit() {};

protected:
    // This should be safe here, since it's literally just a wrapper for an entt::entity type which
    // is a uint32_t. Literally adds only 4 bytes to each component in storage. If you had 10
    // components per entity and 6k entities this only amounts to like and extra 235kb for the entire scene.
    Entity owner;
};
