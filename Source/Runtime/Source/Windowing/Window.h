#pragma once

namespace Diligent
{
    class ImGuiImplWin32;
}

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

    void OnCloseRequested();
    
    void Update();
    void Render();
    
protected:
    void CreateResources();
    
    SDL_Window* windowPtr = nullptr;
    std::shared_ptr<Diligent::ImGuiImplWin32> imguiRenderer = nullptr;
};
