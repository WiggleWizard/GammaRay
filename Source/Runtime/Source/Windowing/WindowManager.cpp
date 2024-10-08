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

    windowRegisteredDelegate.Broadcast(window);
    
    windows.push_back(window);
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
    
    switch (event.type)
    {
    case SDL_WINDOWEVENT:
        OnWindowEvent(reinterpret_cast<SDL_WindowEvent*>(&event));
        break;
    case SDL_MOUSEMOTION:
        OnMouseMove(reinterpret_cast<SDL_MouseMotionEvent*>(&event));
        break;
    case SDL_MOUSEWHEEL:
        OnMouseWheel(reinterpret_cast<SDL_MouseWheelEvent*>(&event));
        break;
    case SDL_MOUSEBUTTONDOWN:
    case SDL_MOUSEBUTTONUP:
        OnMouseButtonPressed(reinterpret_cast<SDL_MouseButtonEvent*>(&event));
        break;
    case SDL_TEXTINPUT:
        OnTextInput(reinterpret_cast<SDL_TextInputEvent*>(&event));
        break;
    case SDL_KEYUP:
    case SDL_KEYDOWN:
        OnKeyboardPressed(reinterpret_cast<SDL_KeyboardEvent*>(&event));
        break;
    case SDL_JOYAXISMOTION:
        OnJoyAxisMotion(reinterpret_cast<SDL_JoyAxisEvent*>(&event));
        break;
    // case SDL_JOYBALLMOTION:
    // case SDL_JOYHATMOTION:
    case SDL_JOYBUTTONDOWN:
    case SDL_JOYBUTTONUP:
        OnJoyButtonPressed(reinterpret_cast<SDL_JoyButtonEvent*>(&event));
        break;
    default: break;
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

void WindowManager::OnMouseMove(const SDL_MouseMotionEvent* event)
{
    auto window = GetWindowFromWindowID(event->windowID);
    if (IsValid(window))
    {
        window->OnMouseMove(event);
    }
}

void WindowManager::OnMouseButtonPressed(const SDL_MouseButtonEvent* event)
{
    auto window = GetWindowFromWindowID(event->windowID);
    if (IsValid(window))
    {
        window->OnMouseButtonPressed(event);
    }
}

void WindowManager::OnMouseWheel(const SDL_MouseWheelEvent* event)
{
    auto window = GetWindowFromWindowID(event->windowID);
    if (IsValid(window))
    {
        window->OnMouseWheel(event);
    }
}

void WindowManager::OnKeyboardPressed(const SDL_KeyboardEvent* event)
{
    auto focusedWindow = GetFocusedWindow();
    if (IsValid(focusedWindow))
    {
        focusedWindow->OnKeyboardPressed(event);
    }
}

void WindowManager::OnJoyAxisMotion(SDL_JoyAxisEvent* event)
{
    auto focusedWindow = GetFocusedWindow();
    if (IsValid(focusedWindow))
    {
        
    }
}

void WindowManager::OnJoyButtonPressed(SDL_JoyButtonEvent* event)
{
    auto focusedWindow = GetFocusedWindow();
    if (IsValid(focusedWindow))
    {
        
    }
}

void WindowManager::OnTextInput(const SDL_TextInputEvent* event)
{
    auto window = GetWindowFromWindowID(event->windowID);
    if (IsValid(window))
    {
        window->OnTextInput(event);
    }
}

void WindowManager::SendEventToFocusedWindow(const SDL_Event* event)
{
}

