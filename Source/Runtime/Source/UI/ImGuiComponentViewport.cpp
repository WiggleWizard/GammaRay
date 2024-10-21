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
            ImGuiWindowResized(viewSize.x, viewSize.y);
            
            prevSizeX = viewSize.x;
            prevSizeY = viewSize.y;
        }

        if (IsValid(viewport))
        {
            ImGui::Image(viewport->GetRenderResourceShader(), ImGui::GetContentRegionAvail());

            // Force ImGui to not sink the inputs if we are hovering over the viewport display quad
            auto& io = ImGui::GetIO();
            if (ImGui::IsItemHovered())
            {
                io.WantCaptureMouse = false;
                io.WantCaptureKeyboard = false;
            }
        }
    }
    ImGui::End();

    ImGui::PopID();
}

void ImGuiComponentViewport::ImGuiWindowResized(uint32 width, uint32 height)
{
    viewport->Resize(width, height);
}
