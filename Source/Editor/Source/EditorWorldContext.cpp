#include "EditorWorldContext.h"

#include "EditorWorld.h"
#include "GameWorld.h"

EditorWorldContext::EditorWorldContext()
{
    editorWorld = NewObject<EditorWorld>();
    gameWorld = NewObject<GameWorld>();
}

void EditorWorldContext::Process()
{
    WorldContext::Process();

    gameWorld->Process();
}

void EditorWorldContext::Initialize()
{
    gameWorld->Initialize();
}

ObjectPtr<World> EditorWorldContext::GetMainWorld()
{
    return editorWorld;
}
