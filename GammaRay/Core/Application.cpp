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

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

    float vertices[3 * 3] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

    glGenBuffers(1, &vertexIndex);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexIndex);

    unsigned int indices[3] = {0, 1, 2};
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

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
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

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
