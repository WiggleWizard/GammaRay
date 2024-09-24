#pragma once

struct SDL_Window;

class Window : public Object
{
public:
    Window(const String& windowTitle);
    ~Window();

    uint32 GetWindowID();

    void OnCloseRequested();
    
protected:
    SDL_Window* windowPtr = nullptr;
};
