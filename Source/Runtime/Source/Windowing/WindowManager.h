#pragma once
#include <SDL_events.h>

class InputEvent;
class Window;
union SDL_Event;

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
    
    void OnWindowEvent(const SDL_WindowEvent* event);
    void PropagateInputEvent(const InputEvent* inputEvent);

private:
    void SendEventToFocusedWindow(const SDL_Event* event);
    
    std::vector<ObjectPtr<Window>> windows = {};
};
