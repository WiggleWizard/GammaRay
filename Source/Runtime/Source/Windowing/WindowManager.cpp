#include "WindowManager.h"

#include <SDL.h>

DEFINE_LOGGER_STATIC(LogWindowManager, LogVerbosity::Verbose);

void WindowManager::Initialize()
{
    const int sdlResult = SDL_Init(SDL_INIT_VIDEO);
    if (sdlResult != 0)
    {
        LogWindowManager.Critical("Could not initialize SDL, error {}", sdlResult);
        return;
    }
}

void WindowManager::NewWindow(const StringName windowTitle)
{
    SDL_Window* window = SDL_CreateWindow(windowTitle.GetString().c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    if (window == nullptr)
    {
        LogWindowManager.Critical("Could not create a new window");
        return;
    }
    
    windows.push_back(window);
}
