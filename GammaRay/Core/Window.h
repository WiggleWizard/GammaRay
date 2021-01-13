#pragma once

#include "grpch.h"

#include "Core/Core.h"
#include "Core/Event/Event.h"


struct WindowProps
{
    WindowID windowId = 0;
    std::string title;
    Size2i windowSize;
    Color clearColor;

    WindowProps(const std::string& windowTitle = "GammaRay Engine", const Size2i& windowSize = Size2i(800, 600), const Color& color = {0.1f})
        : title(windowTitle)
        , windowSize(windowSize)
        , clearColor(color)
    {}
};

// Generic interface representing a DWM window
class GAMMARAY_API Window
{
public:
    using EventCallbackFn = std::function<void(Event&)>;

    virtual ~Window() {}

    virtual void PreRender() = 0;
    virtual void OnUpdate() = 0;

    virtual Size2i GetSize() const = 0;

    virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
    virtual void SetVSync(bool enabled) = 0;
    virtual bool IsVSync() const = 0;

    virtual void* GetNativeWindow() const = 0;

    virtual bool IsMouseLocked() const = 0;
    virtual void LockMouse() = 0;
    virtual void UnlockMouse() = 0;

    static Window* Create(const WindowProps& props = WindowProps());
};
