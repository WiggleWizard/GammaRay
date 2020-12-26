#include "grpch.h"
#include "Window.h"

#include "Core/Debug/Log.h"

#include <GLFW/glfw3.h>


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
        GR_CORE_ASSERT(success, "Could not initialize GLFW");
        m_glfwInitialized = success;
    }

    m_glfwWindow = glfwCreateWindow(m_data.width, m_data.height, m_data.title.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(m_glfwWindow);
    glfwSetWindowUserPointer(m_glfwWindow, &m_data);
    SetVSync(true);
}

void WindowsWindow::Shutdown()
{
    glfwDestroyWindow(m_glfwWindow);
}
