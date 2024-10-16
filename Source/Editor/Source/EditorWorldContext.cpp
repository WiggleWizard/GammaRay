#include "EditorWorldContext.h"

#include "GameWorld.h"

EditorWorldContext::EditorWorldContext()
{
    gameWorld = NewObject<GameWorld>();
}

ObjectPtr<World> EditorWorldContext::GetMainWorld()
{
    return gameWorld;
}
