#include "grpch.h"
#include "Window.h"

#include "Core/Debug/Log.h"

#include "Core/Event/Event.h"
#include "Core/Event/EventKey.h"
#include "Core/Event/EventMouse.h"
#include "Core/Event/EventWindow.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>


bool WindowsWindow::m_glfwInitialized = false;

Window* Window::Create(const WindowProps& props)
{
    return new WindowsWindow(props);
}

WindowsWindow::WindowsWindow(const WindowProps& props)
{
    Init(props);
}

WindowsWindow::~WindowsWindow()
{
}

void WindowsWindow::OnUpdate()
{
    const Color& clearColor = m_data.clearColor;
    glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwPollEvents();
    glfwSwapBuffers(m_glfwWindow);
}

void WindowsWindow::SetVSync(bool enabled)
{
    glfwSwapInterval(enabled ? 1 : 0);
    m_data.vsyncEnabled = enabled;
}

bool WindowsWindow::IsVSync() const
{
    return m_data.vsyncEnabled;
}

void WindowsWindow::Init(const WindowProps& props)
{
    m_data.title      = props.title;
    m_data.width      = props.width;
    m_data.height     = props.height;
    m_data.clearColor = props.clearColor;

    GR_CORE_INFO("Creating window {0} ({1}, {2})", m_data.title, m_data.width, m_data.height);

    if(!m_glfwInitialized)
    {
        int success = glfwInit();
        glfwSetErrorCallback(&WindowsWindow::OnGLFWError);
        GR_CORE_ASSERT(success, "Could not initialize GLFW");
        m_glfwInitialized = success;
    }

    m_glfwWindow = glfwCreateWindow(m_data.width, m_data.height, m_data.title.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(m_glfwWindow);

    int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    GR_CORE_ASSERT(!status, "glad failed to load");

    glfwSetWindowUserPointer(m_glfwWindow, &m_data);
    SetVSync(true);

    SetupGLFWCallbacks();
}

void WindowsWindow::SetupGLFWCallbacks()
{
    glfwSetWindowSizeCallback(m_glfwWindow, [](GLFWwindow* window, int w, int h)
    {
        WindowData* windowData = (WindowData*)glfwGetWindowUserPointer(window);
        windowData->height = h;
        windowData->width = w;

        EventWindowResize event(w, h);
        windowData->eventCallback(event);
    });

    glfwSetWindowCloseCallback(m_glfwWindow, [](GLFWwindow* window)
    {
        WindowData* windowData = (WindowData*)glfwGetWindowUserPointer(window);

        EventWindowClose event;
        windowData->eventCallback(event);
    });

    glfwSetKeyCallback(m_glfwWindow, [](GLFWwindow* window, int key, int scanCode, int action, int mods)
    {
        WindowData* windowData = (WindowData*)glfwGetWindowUserPointer(window);

        switch(action)
        {
            case GLFW_PRESS:
            {
                EventKeyPressed event(key, 0);
                windowData->eventCallback(event);
            } break;
            case GLFW_RELEASE:
            {
                EventKeyReleased event(key);
                windowData->eventCallback(event);
            } break;
            case GLFW_REPEAT:
            {
                EventKeyPressed event(key, 1);
                windowData->eventCallback(event);
            } break;
            default: break;
        }
    });

    glfwSetMouseButtonCallback(m_glfwWindow, [](GLFWwindow* window, int button, int action, int mods)
    {
        WindowData* windowData = (WindowData*)glfwGetWindowUserPointer(window);

        switch(action)
        {
            case GLFW_PRESS:
            {
                EventMousePressed event(button);
                windowData->eventCallback(event);
            } break;
            case GLFW_RELEASE:
            {
                EventMouseRelease event(button);
                windowData->eventCallback(event);
            } break;
            default: break;
        }
    });

    // TODO: Mouse scroll

    glfwSetCursorPosCallback(m_glfwWindow, [](GLFWwindow* window, double x, double y)
    {
        WindowData* windowData = (WindowData*)glfwGetWindowUserPointer(window);

        EventMouseMoved event((float)x, (float)y);
        windowData->eventCallback(event);
    });
}

void WindowsWindow::Shutdown()
{
    glfwDestroyWindow(m_glfwWindow);
}
