#include "grpch.h"
#include "WindowsWindow.h"

#include "Core/Debug/Log.h"

#include "Core/Event/Event.h"
#include "Core/Event/EventKey.h"
#include "Core/Event/EventMouse.h"
#include "Core/Event/EventWindow.h"

#include "Core/Input/Input.h"
#include "Core/Input/InputEvent.h"

#include "Drivers/OpenGL3/GraphicsContextOpenGL3.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>


Window* Window::Create(const WindowProps& props)
{
    return new WindowsWindow(props);
}

bool WindowsWindow::m_glfwInitialized = false;

WindowsWindow::WindowsWindow(const WindowProps& props)
{
    Init(props);
}

WindowsWindow::~WindowsWindow()
{
}

void WindowsWindow::PreRender()
{
    const Color& clearColor = m_data.clearColor;
    glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void WindowsWindow::OnUpdate()
{
    glfwPollEvents();
    m_renderingSystem->SwapBuffers();
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

bool WindowsWindow::IsMouseLocked() const
{
    return glfwGetInputMode(m_glfwWindow, GLFW_CURSOR) == GLFW_CURSOR_DISABLED;
}

void WindowsWindow::LockMouse()
{
    glfwSetInputMode(m_glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void WindowsWindow::UnlockMouse()
{
    glfwSetInputMode(m_glfwWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void WindowsWindow::Init(const WindowProps& props)
{
    m_data.title = props.title;
    m_data.windowSize = props.windowSize;
    m_data.clearColor = props.clearColor;

    GR_CORE_INFO("Creating window {0} ({1}, {2})", m_data.windowSize.x, m_data.windowSize.y);

    if(!m_glfwInitialized)
    {
        int success = glfwInit();
        glfwSetErrorCallback(&WindowsWindow::OnGLFWError);
        GR_CORE_ASSERT(success, "Could not initialize GLFW");
        m_glfwInitialized = success;

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    }

    m_glfwWindow = glfwCreateWindow(m_data.windowSize.x, m_data.windowSize.y, m_data.title.c_str(), nullptr, nullptr);

    m_renderingSystem = new GraphicsContextOpenGL3();
    m_renderingSystem->SetGLFWContext(m_glfwWindow);
    m_renderingSystem->Init();

    glfwSetWindowUserPointer(m_glfwWindow, &m_data);
    SetVSync(true);

    SetupGLFWCallbacks();

    UnlockMouse();

    glEnable(GL_DEPTH_TEST);
}

void WindowsWindow::SetupGLFWCallbacks()
{
    glfwSetWindowSizeCallback(m_glfwWindow, [](GLFWwindow* window, int w, int h)
    {
        WindowData* windowData = (WindowData*)glfwGetWindowUserPointer(window);
        windowData->windowSize.x = h;
        windowData->windowSize.y = w;

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

        InputEventKey event;

        switch(action)
        {
        case GLFW_PRESS:
        {
            event.keycode = key;
            event.pressed = true;
            event.echo    = false;
        } break;
        case GLFW_RELEASE:
        {
            event.keycode = key;
            event.pressed = false;
            event.echo    = false;
        } break;
        case GLFW_REPEAT:
        {
            event.keycode = key;
            event.pressed = true;
            event.echo    = true;
        } break;
        default: break;
        }

        Input::GetSingleton()->ProcessWindowInput(event);
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

    glfwSetScrollCallback(m_glfwWindow, [](GLFWwindow* window, double xOffset, double yOffset)
    {
        WindowData* windowData = (WindowData*)glfwGetWindowUserPointer(window);

        EventMouseScrolled event((float)xOffset, (float)yOffset);
        windowData->eventCallback(event);
    });

    glfwSetCursorPosCallback(m_glfwWindow, [](GLFWwindow* window, double x, double y)
    {
        WindowData* windowData = (WindowData*)glfwGetWindowUserPointer(window);

        InputEventMouseMotion event;
        event.position.x = (float)x;
        event.position.y = (float)y;
        Input::GetSingleton()->ProcessWindowInput(event);
    });
}

void WindowsWindow::Shutdown()
{
    glfwDestroyWindow(m_glfwWindow);
}
