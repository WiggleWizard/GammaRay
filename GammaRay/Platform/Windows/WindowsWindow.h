#pragma once

#include "Core/Window.h"
#include "Core/Event/Event.h"

struct GLFWwindow;
class GraphicsContextOpenGL;


class WindowsWindow : public Window
{
public:
    WindowsWindow(const WindowProps& props);
    virtual ~WindowsWindow();

    static void OnGLFWError(int error, const char* description)
    {
        GR_CORE_ERROR("A GLFW error occurred ({0}): {1}", error, description);
    }

    void PreRender() override;
    void OnUpdate() override;

    inline virtual Size2i GetSize() const { return m_data.windowSize; }

    virtual void SetEventCallback(const EventCallbackFn& callback) override { m_data.eventCallback = callback; }
    virtual void SetVSync(bool enabled) override;
    virtual bool IsVSync() const override;

    virtual void* GetNativeWindow() const override { return (void*)m_glfwWindow; }

    virtual bool IsMouseLocked() const override;
    virtual void LockMouse() override;
    virtual void UnlockMouse() override;
private:
    virtual void Init(const WindowProps& props);
    virtual void SetupGLFWCallbacks();
    virtual void Shutdown();

private:
    // TODO: Who owns this GLFW window???
    GLFWwindow* m_glfwWindow = nullptr;
    GraphicsContextOpenGL* m_renderingSystem = nullptr;

    struct WindowData
    {
        std::string title;
        Size2i windowSize;
        Color clearColor;
        bool vsyncEnabled;

        EventCallbackFn eventCallback;
    } m_data;

    static bool m_glfwInitialized;
};
