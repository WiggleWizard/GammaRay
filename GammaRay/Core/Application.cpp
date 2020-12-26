#include "grpch.h"
#include "Application.h"

#include "Window.h"


Application* Application::singleton = nullptr;

Application::Application()
{
    singleton = this;

    m_windowMain = std::unique_ptr<Window>(Window::Create());
    m_windowMain->SetEventCallback(BIND_EVENT_FN(OnEvent));
}

Application::~Application()
{
}

bool Application::OnProcess(float DeltaTimeMS)
{
    m_windowMain->OnUpdate();
    return m_running;
}

void Application::OnEvent(Event& event)
{
    EventDispatcher dispatcher(event);
    dispatcher.Dispatch<EventWindowClose>(BIND_EVENT_FN(OnEventWindowClose));

    GR_CORE_TRACE("{0}", event);
}

bool Application::OnEventWindowClose(EventWindowClose& event)
{
    m_running = false;
    return true;
}
