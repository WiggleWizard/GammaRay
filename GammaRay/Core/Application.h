#pragma once

#include "Core.h"


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

};

Application* CreateApplication();
