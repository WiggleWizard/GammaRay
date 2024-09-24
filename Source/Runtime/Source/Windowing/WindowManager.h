#pragma once

class Window;
struct SDL_WindowEvent;

class WindowManager : public Object
{
    DECLARE_CLASS(WindowManager, Object)
    
public:
    WindowManager() {}
    ~WindowManager() {}
    
    void Initialize();
    ObjectPtr<Window> NewWindow(const StringName windowTitle);

    void PollEvents();

private:
    void OnWindowEvent(const SDL_WindowEvent* event);
    
    std::vector<ObjectPtr<Window>> windows = {};
};
