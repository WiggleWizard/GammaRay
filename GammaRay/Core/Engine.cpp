#include "grpch.h"
#include "Engine.h"


Engine* Engine::singleton = nullptr;


Engine* Engine::GetSingleton()
{
    return nullptr;
}

Engine::Engine()
{
    singleton = this;
}

Engine::~Engine()
{
    singleton = nullptr;
}
