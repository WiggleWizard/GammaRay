#include "WindowManager.h"

#include "Engine/Engine.h"
#include "Windowing/Window.h"

#include <SDL.h>

DEFINE_LOGGER_STATIC(LogWindowManager, LogVerbosity::Verbose);

void WindowManager::Initialize()
{
    const int sdlResult = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER);
    if (sdlResult != 0)
    {
        LogWindowManager.Critical("Could not initialize SDL, error {}", sdlResult);
        return;
    }
}

ObjectPtr<Window> WindowManager::NewWindow(const StringName windowTitle)
{
    const auto window = NewObject<Window>(windowTitle.GetString());
    if (window == nullptr)
    {
        LogWindowManager.Critical("Could not create a new window");
        return nullptr;
    }
    
    windows.push_back(window);
}

void WindowManager::PollEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    
    for (const auto& window : windows)
    {
        // If any window has processed this event, then don't bubble it elsewhere
        if (window->ProcessEvent(&event))
        {
            return;
        }
    }

    switch (event.type)
    {
    case SDL_WINDOWEVENT:
        OnWindowEvent(reinterpret_cast<SDL_WindowEvent*>(&event));
        break;
    default: break;
    }
}

void WindowManager::Update()
{
    for (const auto& window : windows)
    {
        window->Update();
    }
}

void WindowManager::OnWindowEvent(const SDL_WindowEvent* event)
{
    switch (event->event)
    {
    case SDL_WINDOWEVENT_CLOSE:
    {
        // Find the right window to close
        for (const auto& window : windows)
        {
            if (window->GetWindowID() == event->windowID)
            {
                window->OnCloseRequested();
            }
        }
    } break;
        
    default: break;
    }
}

