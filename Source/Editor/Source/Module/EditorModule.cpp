#include "EditorModule.h"

#include "../EditorWorldContext.h"
#include "Engine/Engine.h"

void EditorModule::OnEngineInitialized()
{
    GEngine->RegisterMainWorldContext(NewObject<EditorWorldContext>());
    GEngine->NewWindow("Test");
}
