#include "Window.h"

#include <SDL.h>
#include <SDL_syswm.h>

void Present()
{
    
}

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

void* Window::GetWindowNativeID()
{
    SDL_SysWMinfo wmInfo;
    SDL_VERSION(&wmInfo.version);
    SDL_GetWindowWMInfo(windowPtr, &wmInfo);
    return (void*)wmInfo.info.win.window;
}

bool Window::PreProcessEvent(const SDL_Event* event)
{
    //return imguiRenderer->ProcessEvent(event);
    return false;
}

void Window::OnCloseRequested()
{
    
}

bool Window::IsFocused() const
{
    const uint32 windowFlags = SDL_GetWindowFlags(windowPtr);
    return (windowFlags & SDL_WINDOW_INPUT_FOCUS) != 0;
}

void Window::PreProcess()
{
    Render();
    Present();
}

void Window::Render()
{
}

void Window::OnWindowEvent(const SDL_WindowEvent* event)
{
}

void Window::OnMouseMove(const SDL_MouseMotionEvent* event)
{
}

void Window::OnMouseButtonPressed(const SDL_MouseButtonEvent* event)
{
}

void Window::OnMouseWheel(const SDL_MouseWheelEvent* event)
{
}

void Window::OnKeyboardPressed(const SDL_KeyboardEvent* event)
{
}

void Window::OnJoyAxisMotion(SDL_JoyAxisEvent* event)
{
}

void Window::OnJoyButtonPressed(SDL_JoyButtonEvent* event)
{
}

void Window::OnTextInput(const SDL_TextInputEvent* event)
{
}

void Window::AttachViewport(ObjectPtr<WindowViewport> inViewport)
{
    viewport = inViewport;
}

void Window::CreateResources()
{
    
}
