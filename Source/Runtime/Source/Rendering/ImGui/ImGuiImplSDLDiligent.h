#pragma once

#include <ImGuiImplDiligent.hpp>
#include <SDL_events.h>

union SDL_Event;

struct SDL_Window;

class ImGuiImplSDLDiligent : public Dg::ImGuiImplDiligent
{
public:
    static std::unique_ptr<ImGuiImplSDLDiligent> Create(const Dg::ImGuiDiligentCreateInfo& CI, SDL_Window* sdlWindowPtr);
    
    ImGuiImplSDLDiligent(const Dg::ImGuiDiligentCreateInfo& CI, SDL_Window* sdlWindowPtr);
    ~ImGuiImplSDLDiligent();

    virtual void NewFrame(Dg::Uint32 RenderSurfaceWidth, Dg::Uint32 RenderSurfaceHeight, Dg::SURFACE_TRANSFORM SurfacePreTransform) override final;
    
    bool ProcessEvent(const SDL_Event* event);

    void Render(Dg::IDeviceContext* pCtx) override;

private:
    SDL_Window* windowPtr = nullptr;
};
