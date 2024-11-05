#include "ImGuiComponentFileBrowser.h"

#include "Engine/Engine.h"

#include <imgui.h>

void ImGuiComponentFileBrowser::Draw()
{
    auto resourceManager = GEngine->GetResourceManager();
    
    ImGui::PushID(uuid.ToString().c_str());
    
    if (ImGui::Begin("Content Browser"))
    {
        resourceManager->ListDirectories("/");
    }
    ImGui::End();

    ImGui::PopID();
}
