#pragma once
#include "grpch.h"

#include "Core.h"
#include "Core/Event/Event.h"
#include "Core/Event/EventWindow.h"

class Window;

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)


class GAMMARAY_API Application
{
    static Application* singleton;

public:
    static Application* GetSingleton() { return singleton; }

public:
    Application();
    virtual ~Application();

    //virtual void Start() = 0;
    virtual bool OnProcess(float DeltaTimeMS);
    //virtual void Stop() = 0;

    void OnEvent(Event& event);
    bool OnEventWindowClose(EventWindowClose& event);

private:
    bool m_running = true;
    std::unique_ptr<Window> m_windowMain;
};

Application* CreateApplication();
