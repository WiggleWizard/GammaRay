#include "WindowManager.h"

#include "Engine/Engine.h"
#include "Rendering/Renderer3D.h"
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

    GEngine->GetRenderer3D()->RegisterWindow(window);
    
    windows.push_back(window);

    return window;
}

ObjectPtr<Window> WindowManager::GetFocusedWindow()
{
    for (const auto& window : windows)
    {
        if (window->IsFocused())
        {
            return window;
        }
    }

    return nullptr;
}

ObjectPtr<Window> WindowManager::GetWindowFromWindowID(uint32 windowId)
{
    for (const auto& window : windows)
    {
        if (window->GetWindowID() == windowId)
        {
            return window;
        }
    }
    return nullptr;
}

void WindowManager::PollEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    
    for (const auto& window : windows)
    {
        // If any window has processed this event, then don't bubble it elsewhere
        if (window->PreProcessEvent(&event))
        {
            return;
        }
    }
}

void WindowManager::PreProcess()
{
    for (const auto& window : windows)
    {
        window->PreProcess();
    }
}

void WindowManager::OnWindowEvent(const SDL_WindowEvent* event)
{
    bool handled = true;

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
        
    default:
        handled = false;
        break;
    }

    if (!handled)
    {
        LogWindowManager.Warn("Unhandled SDL_WindowEvent {0} (0x{0:X})", event->event);
    }
}

void WindowManager::PropagateInputEvent(const ObjectPtr<InputEvent> inputEvent)
{
    for (const auto& window : windows)
    {
        if (window->ProcessInputEvent(inputEvent))
        {
            break;
        }
    }
}

void WindowManager::SendEventToFocusedWindow(const SDL_Event* event)
{
}

