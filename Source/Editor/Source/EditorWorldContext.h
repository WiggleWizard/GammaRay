#pragma once

#include "Engine/WorldContext.h"

class EditorWorld;
class GameWorld;

class EditorWorldContext : public WorldContext
{
public:
    EditorWorldContext();

    virtual ObjectPtr<World> GetMainWorld() override;
    
private:
    ObjectPtr<EditorWorld> editorWorld = nullptr;
    ObjectPtr<GameWorld> gameWorld = nullptr;
};
