#include "EditorModule.h"

#include "../EditorWindowViewport.h"
#include "../EditorWorldContext.h"
#include "../GameWorld.h"
#include "../Resources/ResourceMasterMaterialGrid.h"

#include "Engine/Engine.h"
#include "Rendering/Renderer3D.h"
#include "Resources/ResourceManager.h"
#include "Windowing/Window.h"

void EditorModule::OnEngineInitialized()
{
    auto resourceManager = GEngine->GetResourceManager();
    resourceManager->AddVirtualResource("/Editor/Materials/MM_Grid", new ResourceMasterMaterialGrid());
    
    auto editorWorld = NewObject<EditorWorldContext>();
    GEngine->RegisterMainWorldContext(editorWorld);

    ObjectPtr<Window> editorWindow = GEngine->NewWindow("Test");

    auto renderer = GEngine->GetRenderer3D();
    auto editorViewport = renderer->NewWindowViewport<EditorWindowViewport>(editorWindow);
    editorWindow->AttachViewport(editorViewport);

    editorWorld->Initialize();
}
