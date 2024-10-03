#pragma once

#include <ImGuiImplDiligent.hpp>
#include <SDL_events.h>

union SDL_Event;

struct SDL_Window;

class ImGuiImplSDLDiligent : public Diligent::ImGuiImplDiligent
{
public:
    static std::unique_ptr<ImGuiImplSDLDiligent> Create(const Diligent::ImGuiDiligentCreateInfo& CI, SDL_Window* sdlWindowPtr);
    
    ImGuiImplSDLDiligent(const Diligent::ImGuiDiligentCreateInfo& CI, SDL_Window* sdlWindowPtr);
    ~ImGuiImplSDLDiligent();

    virtual void NewFrame(Diligent::Uint32 RenderSurfaceWidth, Diligent::Uint32 RenderSurfaceHeight, Diligent::SURFACE_TRANSFORM SurfacePreTransform) override final;
    
    bool ProcessEvent(const SDL_Event* event);

private:
    SDL_Window* windowPtr = nullptr;
};
