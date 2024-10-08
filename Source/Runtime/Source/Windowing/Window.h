#pragma once
#include <SDL_events.h>

class ImGuiComponentViewport;
class RenderTarget;
class ImGuiImplSDLDiligent;
class WindowViewport;

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

    // Return true if the input has been sinked/used
    bool PreProcessEvent(const SDL_Event* event);
    void OnCloseRequested();

    bool IsFocused() const;
    
    void PreProcess();
    void Render();
    
    void OnWindowEvent(const SDL_WindowEvent* event);
    void OnMouseMove(const SDL_MouseMotionEvent* event);
    void OnMouseButtonPressed(const SDL_MouseButtonEvent* event);
    void OnMouseWheel(const SDL_MouseWheelEvent* event);
    void OnKeyboardPressed(const SDL_KeyboardEvent* event);
    void OnJoyAxisMotion(SDL_JoyAxisEvent* event);
    void OnJoyButtonPressed(SDL_JoyButtonEvent* event);
    void OnTextInput(const SDL_TextInputEvent* event);

    void AttachViewport(ObjectPtr<WindowViewport> inViewport);
    
protected:
    void CreateResources();
    
    SDL_Window* windowPtr = nullptr;
    
    ObjectPtr<RenderTarget> renderTarget = nullptr;
    //ObjectPtr<ImGuiComponentViewport> viewport = nullptr;
    ObjectPtr<WindowViewport> viewport = nullptr;

    std::shared_ptr<ImGuiImplSDLDiligent> imguiRenderer = nullptr;
};

