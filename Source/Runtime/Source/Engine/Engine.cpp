#include "Engine.h"

#include "MainLoop.h"
#include "ModuleManager.h"
#include "World.h"
#include "WorldContext.h"
#include "Rendering/Renderer3D.h"
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
    
    renderer3D = NewObject<Renderer3D>();

    ModuleManager::Get().EngineInitialized();
    
    mainLoop->Loop();

    // TODO: Cleanup
}

void Engine::RegisterMainWorldContext(ObjectPtr<WorldContext> context)
{
    worldContext = context;
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

ObjectPtr<Window> Engine::NewWindow(const String& windowTitle)
{
    if (IsValid(windowManager))
    {
        return windowManager->NewWindow(windowTitle);
    }
    return nullptr;
}

void Engine::Process()
{
    if (IsValid(windowManager))
    {
        windowManager->PollEvents();
        windowManager->PreProcess();
    }

    if (IsValid(worldContext))
    {
        worldContext->Process();
    }

    if (IsValid(renderer3D))
    {
        renderer3D->Render();
    }
}

bool Engine::OpenWorld(String url)
{
    if (url.empty())
    {
        
    }

    return false;
}

bool Engine::NewWorld()
{
    return false;    
}

ObjectPtr<Renderer3D> Engine::GetRenderer3D()
{
    return renderer3D;
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
