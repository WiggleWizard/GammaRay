#include "ImGuiComponentViewport.h"

#include "Rendering/RenderTarget.h"

#include <imgui.h>

ImGuiComponentViewport::ImGuiComponentViewport(ObjectPtr<RenderTarget> viewport)
    : viewport(viewport)
{
}

void ImGuiComponentViewport::Draw()
{
    ImGui::PushID(uuid.ToString().c_str());
    
    if (ImGui::Begin("Viewport"))
    {
        ImVec2 viewSize = ImGui::GetContentRegionAvail();
        if (prevSizeX != (uint32)viewSize.x || prevSizeY != (uint32)viewSize.y)
        {
            OnResized(viewSize.x, viewSize.y);
            
            prevSizeX = viewSize.x;
            prevSizeY = viewSize.y;
        }

        if (IsValid(viewport))
        {
            ImGui::Image(viewport->GetRenderResourceShader(), ImGui::GetContentRegionAvail());
        }
    }
    ImGui::End();

    ImGui::PopID();
}

void ImGuiComponentViewport::OnResized(uint32 width, uint32 height)
{
    viewport->Resize(width, height);
}
