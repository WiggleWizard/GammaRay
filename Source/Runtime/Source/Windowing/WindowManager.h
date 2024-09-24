#pragma once

struct SDL_Window;

class WindowManager : public Object
{
    DECLARE_CLASS(WindowManager, Object)
    
public:
    WindowManager() {}
    ~WindowManager() {}
    
    void Initialize();
    void NewWindow(const StringName windowTitle);

private:
    std::vector<SDL_Window*> windows;
};
