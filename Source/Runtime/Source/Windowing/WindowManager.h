#pragma once

class Window;
struct SDL_WindowEvent;
struct SDL_KeyboardEvent;
struct SDL_MouseMotionEvent;
struct SDL_MouseButtonEvent;
struct SDL_MouseWheelEvent;
struct SDL_JoyAxisEvent;
struct SDL_JoyButtonEvent;
struct SDL_TextInputEvent;
union SDL_Event;

DECLARE_MULTICAST_DELEGATE(OnWindowRegisteredDelegate, ObjectPtr<Window>);

class WindowManager : public Object
{
    DECLARE_CLASS(WindowManager, Object)
    
public:
    WindowManager() {}
    ~WindowManager() {}
    
    void Initialize();
    ObjectPtr<Window> NewWindow(const StringName windowTitle);
    ObjectPtr<Window> GetFocusedWindow();
    ObjectPtr<Window> GetWindowFromWindowID(uint32 windowId);

    void PollEvents();
    void PreProcess();

    OnWindowRegisteredDelegate onWindowRegistered() { return windowRegisteredDelegate; }

private:
    void OnWindowEvent(const SDL_WindowEvent* event);
    void OnMouseMove(const SDL_MouseMotionEvent* event);
    void OnMouseButtonPressed(const SDL_MouseButtonEvent* event);
    void OnMouseWheel(const SDL_MouseWheelEvent* event);
    void OnKeyboardPressed(const SDL_KeyboardEvent* event);
    void OnJoyAxisMotion(SDL_JoyAxisEvent* event);
    void OnJoyButtonPressed(SDL_JoyButtonEvent* event);
    void OnTextInput(const SDL_TextInputEvent* event);

    void SendEventToFocusedWindow(const SDL_Event* event);
    
    std::vector<ObjectPtr<Window>> windows = {};
    
    OnWindowRegisteredDelegate windowRegisteredDelegate;
};
