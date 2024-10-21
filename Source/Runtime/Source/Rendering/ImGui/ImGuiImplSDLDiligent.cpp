#include "ImGuiImplSDLDiligent.h"

#include <backends/imgui_impl_sdl.h>
#include <SDL_events.h>

std::unique_ptr<ImGuiImplSDLDiligent> ImGuiImplSDLDiligent::Create(const Diligent::ImGuiDiligentCreateInfo& CI, SDL_Window* sdlWindowPtr)
{
    return std::make_unique<ImGuiImplSDLDiligent>(CI, sdlWindowPtr);
}

ImGuiImplSDLDiligent::ImGuiImplSDLDiligent(const Diligent::ImGuiDiligentCreateInfo& CI, SDL_Window* sdlWindowPtr)
    : ImGuiImplDiligent(CI)
    , windowPtr(sdlWindowPtr)
{
    ImGui_ImplSDL2_InitForSDLRenderer(sdlWindowPtr, nullptr);
}

ImGuiImplSDLDiligent::~ImGuiImplSDLDiligent()
{
    ImGui_ImplSDL2_Shutdown();
}

void ImGuiImplSDLDiligent::NewFrame(Diligent::Uint32 RenderSurfaceWidth, Diligent::Uint32 RenderSurfaceHeight, Diligent::SURFACE_TRANSFORM SurfacePreTransform)
{
    ImGui_ImplSDL2_NewFrame(windowPtr);
    ImGuiImplDiligent::NewFrame(RenderSurfaceWidth, RenderSurfaceHeight, SurfacePreTransform);
}

bool ImGuiImplSDLDiligent::ProcessEvent(const SDL_Event* event)
{
    return ImGui_ImplSDL2_ProcessEvent(event);
}

void ImGuiImplSDLDiligent::Render(Dg::IDeviceContext* pCtx)
{
    pCtx->BeginDebugGroup("ImGui Render");
    ImGuiImplDiligent::Render(pCtx);
    pCtx->EndDebugGroup();
}
