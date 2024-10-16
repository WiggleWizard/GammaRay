#include "EditorModule.h"

#include "../EditorWindowViewport.h"
#include "../EditorWorldContext.h"
#include "../GameWorld.h"

#include "Engine/Engine.h"
#include "Rendering/Renderer3D.h"
#include "Windowing/Window.h"

void EditorModule::OnEngineInitialized()
{
    ObjectPtr<Window> editorWindow = GEngine->NewWindow("Test");

    auto renderer = GEngine->GetRenderer3D();
    auto editorViewport = renderer->NewWindowViewport<EditorWindowViewport>(editorWindow);
    editorWindow->AttachViewport(editorViewport);
    
    GEngine->RegisterMainWorldContext(NewObject<EditorWorldContext>());
}
