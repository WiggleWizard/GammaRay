#include "grpch.h"
#include "Application.h"

#include "Window.h"

#include "Servers/RenderServer.h"
#include "Servers/SceneServer.h"


Application* Application::singleton = nullptr;

Application::Application()
{
    singleton = this;

    m_windowMain = std::unique_ptr<Window>(Window::Create());
    m_windowMain->SetEventCallback(BIND_EVENT_FN(OnEvent));

    m_layerImGui = new LayerImGui();
    PushLayer(m_layerImGui);
}

Application::~Application()
{
}

bool Application::_OnProcess(float deltaTimeMs)
{
    OnProcess(deltaTimeMs);

    m_windowMain->PreRender();

    SceneServer::GetSingleton()->OnUpdate();

    RenderServer::GetSingleton()->OnUpdate();

    for(Layer* layer : m_layerStack)
        layer->OnProcess();

    m_layerImGui->Begin();
    for(Layer* layer : m_layerStack)
        layer->OnImGuiRender();
    m_layerImGui->End();

    m_windowMain->OnUpdate();
    return m_running;
}

void Application::OnEvent(Event& event)
{
    EventDispatcher dispatcher(event);
    dispatcher.Dispatch<EventWindowClose>(BIND_EVENT_FN(OnEventWindowClose));

    for(auto it = m_layerStack.end(); it != m_layerStack.begin(); )
    {
        (*--it)->OnEvent(event);
        if(event.HasBeenHandled())
            break;
    }

    GR_CORE_TRACE("{0}", event);
}

bool Application::OnEventWindowClose(EventWindowClose& event)
{
    m_running = false;
    return true;
}

void Application::PushLayer(Layer* layer)
{
    m_layerStack.PushLayer(layer);
}

Size2i Application::GetWindowSize()
{
    return m_windowMain->GetSize();
}
