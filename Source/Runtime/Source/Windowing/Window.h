#pragma once
#include <SDL_events.h>

class ImGuiImplSDLDiligent;

namespace Diligent
{
    class ImGuiDiligentRenderer;
}

struct SDL_Window;

class Window : public Object
{
public:
    Window(const String& windowTitle);
    ~Window();

    uint32 GetWindowID();
    void* GetWindowNativeID();

    bool ProcessEvent(const SDL_Event* event);
    void OnCloseRequested();
    
    void Update();
    void Render();
    
protected:
    void CreateResources();
    
    SDL_Window* windowPtr = nullptr;
    std::shared_ptr<ImGuiImplSDLDiligent> imguiRenderer = nullptr;
};
