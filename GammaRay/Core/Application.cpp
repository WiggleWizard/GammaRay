#include "grpch.h"
#include "Application.h"

#include "Window.h"

#include "Core/Renderer/Shaders/default.gen.h"

#include <glad/glad.h>


Application* Application::singleton = nullptr;

Application::Application()
{
    singleton = this;

    m_windowMain = std::unique_ptr<Window>(Window::Create());
    m_windowMain->SetEventCallback(BIND_EVENT_FN(OnEvent));

    m_layerImGui = new LayerImGui();
    PushLayer(m_layerImGui);

    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);

    float vertices[3 * 3] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };
    m_vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

    uint32_t indices[3] = {0, 1, 2};
    m_indexBuffer.reset(IndexBuffer::Create(indices, 3));

    m_shader.reset(new RendererShaderDefault());
    m_shader->Compile();
}

Application::~Application()
{
}

bool Application::_OnProcess(float deltaTimeMs)
{
    OnProcess(deltaTimeMs);

    m_windowMain->PreRender();

    m_shader->Bind();
    glBindVertexArray(vertexArray);
    glDrawElements(GL_TRIANGLES, m_indexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

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
