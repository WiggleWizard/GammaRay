#pragma once

#include "Core/Object/Object.h"

class WindowManager;
class ObjectRegistry;
class MainLoop;

class Engine : public Object
{
    DECLARE_CLASS(Engine, Object)

public:
    Engine();
    ~Engine();

    void Initialize();

    void Quit();
    bool WantsToQuit() const;

private:
    bool TryExit();
    void Cleanup();
    
    ObjectPtr<WindowManager> windowManager = nullptr;
    ObjectPtr<MainLoop> mainLoop = nullptr;

    bool wantsToQuit = false;
};

extern ObjectPtr<Engine> GEngine;
