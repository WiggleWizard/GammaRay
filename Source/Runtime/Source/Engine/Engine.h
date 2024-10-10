#pragma once

#include "Core/Object/Object.h"
#include "Core/Object/ObjectMacros.h"
#include "Core/Types/String.h"

class Renderer3D;
class WorldContext;
class WindowManager;
class ObjectRegistry;
class MainLoop;
class Window;

class Engine : public Object
{
    DECLARE_CLASS(Engine, Object)

public:
    Engine();
    ~Engine();

    void Initialize();

    void RegisterMainWorldContext(ObjectPtr<WorldContext> context);
    ObjectPtr<WorldContext> GetMainWorldContext() { return worldContext; }

    void Quit();
    void RequestQuit();
    bool WantsToQuit() const;

    ObjectPtr<Window> NewWindow(const String& windowTitle);

    void Process();

    bool OpenWorld(String url);
    bool NewWorld();

    ObjectPtr<Renderer3D> GetRenderer3D();

private:
    bool TryExit();
    void Cleanup();
    
    ObjectPtr<WindowManager> windowManager = nullptr;
    ObjectPtr<MainLoop> mainLoop = nullptr;
    ObjectPtr<WorldContext> worldContext = nullptr;
    ObjectPtr<Renderer3D> renderer3D = nullptr;

    bool wantsToQuit = false;
};

extern ObjectPtr<Engine> GEngine;
