#include "Engine.h"

#include "Windowing/WindowManager.h"

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
}
