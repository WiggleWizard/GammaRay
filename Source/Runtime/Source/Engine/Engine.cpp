#include "Engine.h"

#include "MainLoop.h"
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
    
    mainLoop->Loop();

    // TODO: Cleanup
}

void Engine::Quit()
{
    wantsToQuit = true;
}

bool Engine::WantsToQuit() const
{
    return wantsToQuit;
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
