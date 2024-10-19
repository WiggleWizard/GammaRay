#pragma once

#include "Engine/WorldContext.h"

class EditorWorld;
class GameWorld;

class EditorWorldContext : public WorldContext
{
public:
    EditorWorldContext();

    void Process() override;

    void Initialize();

    virtual ObjectPtr<World> GetMainWorld() override;

    ObjectPtr<GameWorld> GetGameWorld() { return gameWorld; }
    
private:
    ObjectPtr<EditorWorld> editorWorld = nullptr;
    ObjectPtr<GameWorld> gameWorld = nullptr;
};
