#pragma once


struct ComponentSceneLink
{
    // Used to determine what order this entity is placed in the scene tree
    uint32_t position = 0;
    // Links to the entt RID who this is a child of
    uint32_t parent = 0;

    bool enabled = true;
    uint32_t sceneId;
    std::string entityName;
};
