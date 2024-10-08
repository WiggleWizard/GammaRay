#include "ImGuiComponentViewport.h"

#include "Rendering/RenderTarget.h"

#include <imgui.h>
#include <SwapChain.h>
#include <RenderDevice.h>

namespace Dg = Diligent;

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
        if (prevWindowSize.x != (uint32)viewSize.x || prevWindowSize.y != (uint32)viewSize.y)
        {
            //OnResized(viewSize.x, viewSize.y);
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
}
