#pragma once

class InputEvent;
class ImGuiComponentViewport;
class RenderTarget;
class ImGuiImplSDLDiligent;
class WindowViewport;

struct SDL_Window;
struct SDL_WindowEvent;
struct SDL_KeyboardEvent;
struct SDL_MouseMotionEvent;
struct SDL_MouseButtonEvent;
struct SDL_MouseWheelEvent;
struct SDL_JoyAxisEvent;
struct SDL_JoyButtonEvent;
struct SDL_TextInputEvent;
union SDL_Event;

class Window : public Object
{
public:
    Window(const String& windowTitle);
    ~Window();

    uint32 GetWindowID();
    void* GetWindowNativeID();

    // Return true if the input has been sinked/used
    bool ProcessEventForImGui(const SDL_Event* event);
    void OnCloseRequested();

    bool IsFocused() const;
    
    void PreProcess();
    void Render();

    virtual bool ProcessInputEvent(const ObjectPtr<InputEvent> inputEvent);

    void AttachViewport(ObjectPtr<WindowViewport> inViewport);
    
protected:
    void CreateResources();
    
    SDL_Window* windowPtr = nullptr;
    
    ObjectPtr<RenderTarget> renderTarget = nullptr;
    //ObjectPtr<ImGuiComponentViewport> viewport = nullptr;

    // Non-owned viewport reference
    ObjectPtr<WindowViewport> viewport = nullptr;
};

