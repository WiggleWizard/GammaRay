#include "grpch.h"
#include "Application.h"

#include "Window.h"


Application* Application::singleton = nullptr;

Application::Application()
{
    singleton = this;
    m_windowMain = std::unique_ptr<Window>(Window::Create());
}

Application::~Application()
{
}

void Application::Step(float DeltaTimeMS)
{
    while(true)
    {
        m_windowMain->OnUpdate();
    }
}
