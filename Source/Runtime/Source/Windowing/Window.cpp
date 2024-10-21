#include "Window.h"

#include "Rendering/WindowViewport.h"
#include "Rendering/ImGui/ImGuiImplSDLDiligent.h"

#include <imgui.h>
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
    if (IsValid(viewport))
    {
        return viewport->PreProcessEvent(event);
    }
    
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
    if (IsValid(viewport))
    {
        viewport->PreProcess();
    }
}

void Window::Render()
{
}

bool Window::ProcessInputEvent(const ObjectPtr<InputEvent> inputEvent)
{
    // Tell the active viewport to process the input
    viewport->ProcessInputEvent(inputEvent);
    
    return false;
}

void Window::AttachViewport(ObjectPtr<WindowViewport> inViewport)
{
    viewport = inViewport;

    Diligent::ImGuiDiligentCreateInfo imguiCreateInfo;
    imguiCreateInfo.pDevice = viewport->GetRenderDevice();
    auto swapChain = viewport->GetSwapChain();
    imguiCreateInfo.BackBufferFmt = swapChain->GetDesc().ColorBufferFormat;
    imguiCreateInfo.DepthBufferFmt = swapChain->GetDesc().DepthBufferFormat;
    viewport->SetImguiRenderer(new ImGuiImplSDLDiligent(imguiCreateInfo, windowPtr));
}

void Window::CreateResources()
{
    
}
