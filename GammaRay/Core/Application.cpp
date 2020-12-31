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

    m_vertexArray.reset(VertexArray::Create());

    float vertices[3 * 7] = {
        -0.5f, -0.5f, 0.0f,  0.8, 0.2, 0.8, 1.0,
        0.5f, -0.5f, 0.0f,   0.2, 0.3, 0.8, 1.0,
        0.0f, 0.5f, 0.0f,    0.8, 0.8, 0.2, 1.0,
    };
    m_vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

    BufferLayout layout = {
        { ShaderDataType::Float3, "a_Position" },
        { ShaderDataType::Float4, "a_Color" },
    };
    m_vertexBuffer->SetLayout(layout);
    m_vertexArray->AddVertexBuffer(m_vertexBuffer);

    uint32_t indices[3] = {0, 1, 2};
    m_indexBuffer.reset(IndexBuffer::Create(indices, 3));
    m_vertexArray->AddIndexBuffer(m_indexBuffer);





    m_squareVA.reset(VertexArray::Create());

    float squareVertices[3 * 3 * 4] = {
        -0.5f, -0.5f, 0.0f,  0.8, 0.2, 0.8, 1.0,
        0.5f, -0.5f, 0.0f,   0.2, 0.3, 0.8, 1.0,
        0.0f, 0.5f, 0.0f,    0.8, 0.8, 0.2, 1.0,
        0.5f, 0.5f, 0.0f,    1.0, 0.8, 0.2, 1.0,
    };
    std::shared_ptr<VertexBuffer> squareVB;
    squareVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
    squareVB->SetLayout({
        { ShaderDataType::Float3, "a_Position" },
        { ShaderDataType::Float4, "a_Color" },
    });
    m_squareVA->AddVertexBuffer(squareVB);

    uint32_t squareIndices[6] = {0, 1, 2, 2, 3, 0};
    std::shared_ptr<IndexBuffer> squareIB;
    squareIB.reset(IndexBuffer::Create(squareIndices, 6));
    m_squareVA->AddIndexBuffer(squareIB);







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
    //m_vertexArray->Bind();
    m_squareVA->Bind();

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

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
