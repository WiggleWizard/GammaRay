#pragma once

#include "Core/Object/Object.h"
#include "Core/Object/ObjectMacros.h"
#include "Core/Types/String.h"

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
    void RequestQuit();
    bool WantsToQuit() const;

    void NewWindow(const String& windowTitle);

    void Process();

private:
    bool TryExit();
    void Cleanup();
    
    ObjectPtr<WindowManager> windowManager = nullptr;
    ObjectPtr<MainLoop> mainLoop = nullptr;

    bool wantsToQuit = false;
};

extern ObjectPtr<Engine> GEngine;
