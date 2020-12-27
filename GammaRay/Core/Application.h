#pragma once
#include "grpch.h"

#include "Core.h"
#include "Core/Event/Event.h"
#include "Core/Event/EventWindow.h"
#include "Core/LayerStack.h"

class Window;
class Layer;

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)


class GAMMARAY_API Application
{
    static Application* singleton;

public:
    static Application* GetSingleton() { return singleton; }

public:
    Application();
    virtual ~Application();

    virtual bool OnProcess(float deltaTimeMs) = 0;

    bool _OnProcess(float deltaTimeMs);

    void OnEvent(Event& event);
    bool OnEventWindowClose(EventWindowClose& event);

    void PushLayer(Layer* layer);

    Size2i GetWindowSize(); 

private:
    bool m_running = true;
    std::unique_ptr<Window> m_windowMain;
    LayerStack m_layerStack;
};

Application* CreateApplication();
