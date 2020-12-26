#pragma once

#include "Core.h"
#include "grpch.h"

class Window;


class GAMMARAY_API Application
{
    static Application* singleton;

public:
    static Application* GetSingleton() { return singleton; }

public:
    Application();
    virtual ~Application();

    //virtual void Start() = 0;
    virtual void Step(float DeltaTimeMS);
    //virtual void Stop() = 0;

private:
    std::unique_ptr<Window> m_windowMain;
};

Application* CreateApplication();
