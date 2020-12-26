#pragma once

#include "Core/Window.h"
#include "Core/Event/Event.h"

class GLFWwindow;


class WindowsWindow : public Window
{
public:
    WindowsWindow(const WindowProps& props);
    virtual ~WindowsWindow();

    static void OnGLFWError(int error, const char* description)
    {
        GR_CORE_ERROR("A GLFW error occurred ({0}): {1}", error, description);
    }

    void OnUpdate() override;

    inline virtual unsigned int GetWidth() const { return m_data.width; }
    inline virtual unsigned int GetHeight() const { return m_data.height; }

    virtual void SetEventCallback(const EventCallbackFn& callback) override { m_data.eventCallback = callback; }
    virtual void SetVSync(bool enabled) override;
    virtual bool IsVSync() const override;

private:
    virtual void Init(const WindowProps& props);
    virtual void SetupGLFWCallbacks();
    virtual void Shutdown();

private:
    GLFWwindow* m_glfwWindow;

    struct WindowData
    {
        std::string title;
        unsigned int width;
        unsigned int height;
        Color clearColor;
        bool vsyncEnabled;

        EventCallbackFn eventCallback;
    } m_data;

    static bool m_glfwInitialized;
};
