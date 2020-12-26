#include "grpch.h"
#include "Application.h"


Application* Application::singleton = nullptr;


Application::Application()
{
    singleton = this;
}

Application::~Application()
{
}

void Application::Step(float DeltaTimeMS)
{
    
}
