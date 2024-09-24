#include "Engine.h"

#include "MainLoop.h"
#include "ModuleManager.h"
#include "Windowing/WindowManager.h"

DEFINE_LOGGER_STATIC(LogEngine, LogVerbosity::VeryVerbose)

ObjectPtr<Engine> GEngine = nullptr;

Engine::Engine()
{
}

Engine::~Engine()
{
}

void Engine::Initialize()
{
    windowManager = NewObject<WindowManager>();
    windowManager->Initialize();

    if (TryExit())
        return;

    mainLoop = NewObject<MainLoop>();
    mainLoop->Intialize();

    if (TryExit())
        return;

    ModuleManager::Get().EngineInitialized();
    
    mainLoop->Loop();

    // TODO: Cleanup
}

void Engine::Quit()
{
    wantsToQuit = true;
}

void Engine::RequestQuit()
{
    Quit();
}

bool Engine::WantsToQuit() const
{
    return wantsToQuit;
}

void Engine::NewWindow(const String& windowTitle)
{
    if (IsValid(windowManager))
    {
        windowManager->NewWindow(windowTitle);
    }
}

void Engine::Process()
{
    if (IsValid(windowManager))
    {
        windowManager->PollEvents();
    }
}

bool Engine::TryExit()
{
    bool shouldExit = false;
    if (wantsToQuit)
        shouldExit = true;

    if (!shouldExit)
    {
        return false;
    }
    
    LogEngine.Info("Engine exiting");

    Cleanup();

    return true;
}

void Engine::Cleanup()
{
}
