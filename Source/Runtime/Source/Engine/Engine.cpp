#include "Engine.h"

#include "MainLoop.h"
#include "ModuleManager.h"
#include "World.h"
#include "WorldContext.h"
#include "Input/InputManager.h"
#include "Rendering/Renderer3D.h"
#include "Windowing/WindowManager.h"
#include "Resources/ResourceManager.h"

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
    inputManager = NewObject<InputManager>();
    
    windowManager = NewObject<WindowManager>();
    windowManager->Initialize();

    if (TryExit())
        return;

    mainLoop = NewObject<MainLoop>();
    mainLoop->Intialize();

    if (TryExit())
        return;
    
    renderer3D = NewObject<Renderer3D>();
    resourceManager = NewObject<ResourceManager>();

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
    if (IsValid(inputManager))
    {
        inputManager->PollEvents();
    }
    
    if (IsValid(windowManager))
    {
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
