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

    float vertices[3 * 7] = {
        -0.5f, -0.5f, 0.0f,  0.8, 0.2, 0.8, 1.0,
        0.5f, -0.5f, 0.0f,   0.2, 0.3, 0.8, 1.0,
        0.0f, 0.5f, 0.0f,    0.8, 0.8, 0.2, 1.0,
    };
    m_vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

    {
        BufferLayout layout = {
            { ShaderDataType::Float3, "a_Position" },
            { ShaderDataType::Float4, "a_Color" },
        };
        m_vertexBuffer->SetLayout(layout);
    }

    uint32_t index = 0;
    const auto& layout = m_vertexBuffer->GetLayout();
    for(const auto& element : layout)
    {
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(
            index,
            element.GetComponentCount(),
            ShaderDataTypeToOpenGL(element.type),
            element.normalized ? GL_TRUE : GL_FALSE,
            layout.GetStride(),
            (const void*)element.offset
        );

        index++;
    }

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
