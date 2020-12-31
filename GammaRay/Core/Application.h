#pragma once
#include "grpch.h"

#include "Core.h"
#include "Core/Object/Reference.h"
#include "Core/Event/Event.h"
#include "Core/Event/EventWindow.h"
#include "Core/LayerStack.h"
#include "Core/Window.h"

#include "Core/Layer.h"
#include "Core/Debug/LayerImGui.h"

#include "Core/Renderer/Buffer.h"
#include "Core/Renderer/RendererShader.h"
#include "Core/Renderer/VertexArray.h"

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)


class GAMMARAY_API Application
{
    static Application* singleton;

public:
    static Application* GetSingleton() { return singleton; }

public:
    Application();
    virtual ~Application();

    virtual bool OnProcess(float deltaTimeMs) = 0;

    bool _OnProcess(float deltaTimeMs);

    void OnEvent(Event& event);
    bool OnEventWindowClose(EventWindowClose& event);

    void PushLayer(Layer* layer);

    Ref<Window> GetWindow() { return m_windowMain; }
    Size2i GetWindowSize();

private:
    bool m_running = true;
    Ref<Window> m_windowMain;
    LayerImGui* m_layerImGui;
    LayerStack m_layerStack;

protected:
    std::shared_ptr<VertexArray> m_vertexArray;
    std::shared_ptr<VertexBuffer> m_vertexBuffer;
    std::shared_ptr<IndexBuffer> m_indexBuffer;

    std::shared_ptr<VertexArray> m_squareVA;

    unsigned int vertexArray, vertexBuffer, vertexIndex;
    std::unique_ptr<RendererShader> m_shader;

};

Application* CreateApplication();
