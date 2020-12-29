#pragma once

#include "Core/Renderer/GraphicsContext.h"
#include <glfw/glfw3.h>


class GraphicsContextOpenGL3 : public GraphicsContext
{
public:
    void Init() override;
    void Draw() override;
    void SwapBuffers() override;

    void SetGLFWContext(GLFWwindow* glfwWindow);

    GraphicsContextOpenGL3();
    ~GraphicsContextOpenGL3();

private:
    GLFWwindow* m_windowHandle = nullptr;
};

