#include "EditorModule.h"

#include "Engine/Engine.h"

void EditorModule::OnEngineInitialized()
{
    GEngine->NewWindow("Test");
}
