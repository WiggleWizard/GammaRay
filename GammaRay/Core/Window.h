#pragma once

#include "grpch.h"

#include "Core/Core.h"
#include "Core/Event/Event.h"


struct WindowProps
{
    std::string title;
    unsigned int width;
    unsigned int height;
    Color clearColor;

    WindowProps(const std::string& windowTitle = "GammaRay Engine", unsigned int w = 800, unsigned int h = 600)
        : title(windowTitle)
        , width(w)
        , height(h)
        , clearColor(1, 0, 1)
    {}
};

// Generic interface representing a DWM window
class GAMMARAY_API Window
{
public:
    using EventCallbackFn = std::function<void(Event&)>;

    virtual ~Window() {}

    virtual void OnUpdate() = 0;

    virtual unsigned int GetWidth() const = 0;
    virtual unsigned int GetHeight() const = 0;

    virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
    virtual void SetVSync(bool enabled) = 0;
    virtual bool IsVSync() const = 0;

    static Window* Create(const WindowProps& props = WindowProps());
};
