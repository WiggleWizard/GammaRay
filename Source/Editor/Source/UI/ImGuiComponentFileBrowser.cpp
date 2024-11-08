#include "ImGuiComponentFileBrowser.h"

#include "Engine/Engine.h"
#include "Resources/ResourceManager.h"

#include <imgui.h>

void ImGuiComponentFileBrowser::Draw()
{
    static float leftPaneWidth = 200.0f;
    
    auto resourceManager = GEngine->GetResourceManager();
    
    ImGui::PushID(uuid.ToString().c_str());
    
    if (ImGui::Begin("Content Browser"))
    {
        // Split view
        ImGui::Columns(2, "FileBrowserColumns", true);
        ImGui::SetColumnWidth(0, leftPaneWidth);

        // Left pane - Directory tree
        if (ImGui::Button("Parent Directory"))
        {
            if (currentDir.HasParentPath())
            {
                currentDir.Back();
            }
        }

        ImGui::SameLine();
        
        if (ImGui::Button("Import..."))
        {
            resourceManager->ImportSource("C:/Projects/CPP/GammaRay/teapot.obj", "/Content/Objects/teapot");
        }
        
        auto dirs = resourceManager->ListDirectories(currentDir.ToString());
        for (const auto entry : dirs)
        {
            std::string dirName = entry.name;
            if (ImGui::Selectable(dirName.c_str(), false, ImGuiSelectableFlags_AllowDoubleClick))
            {
                if (ImGui::IsMouseDoubleClicked(0))
                {
                    currentDir /= dirName;
                }
            }
        }

        ImGui::NextColumn();

        // Right pane - File listing
        ImGui::Text("Current Path: %s", currentDir.ToString().c_str());
        ImGui::Separator();

        // Show files
        auto files = resourceManager->ListFiles(currentDir.ToString());
        for (const auto& entry : files)
        {
            if (ImGui::Selectable(entry.name.c_str()))
            {
                // selectedFile = fileName;
                // fileSelected = true;
            }
        }

        ImGui::Columns(1);
    }
    ImGui::End();

    ImGui::PopID();
}
