#include "EditorWindowViewport.h"

#include "EditorWorldContext.h"
#include "GameWorld.h"
#include "UI/ImGuiComponentViewport.h"

#include "../../Runtime/ThirdParty/DiligentTools/ThirdParty/imgui/imgui.h"
#include "Engine/Engine.h"

EditorWindowViewport::EditorWindowViewport(Dg::RefCntAutoPtr<Dg::ISwapChain>& swapChain, Dg::RefCntAutoPtr<Dg::IRenderDevice>& renderDevice)
    : Super(swapChain, renderDevice)
{
    ObjectPtr<Viewport> gameViewport = NewObject<Viewport>(swapChain, renderDevice);
    AttachChildViewport(gameViewport);

    auto editorWorldContext = Cast<EditorWorldContext>(GEngine->GetMainWorldContext());
    if (IsValid(editorWorldContext))
    {
        gameViewport->SetWorld(editorWorldContext->GetGameWorld());
    }

    imGuiComponentViewport = NewObject<ImGuiComponentViewport>(gameViewport);
}

void EditorWindowViewport::DrawImGui()
{
    ImGui::ShowDemoWindow(&imguiDemoWindowOpen);

    imGuiComponentViewport->Draw();
}
