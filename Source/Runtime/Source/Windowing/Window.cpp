#include "Window.h"

#include <SDL_video.h>

Window::Window(const String& windowTitle)
{
    windowPtr = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
}

Window::~Window()
{
}

uint32 Window::GetWindowID()
{
    uint32 windowID = 0;
    
    if (windowPtr != nullptr)
    {
        windowID = SDL_GetWindowID(windowPtr);
    }

    return windowID;
}

void Window::OnCloseRequested()
{
    
}
