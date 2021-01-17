#pragma once

#include "Core/Renderer/GraphicsContext.h"
#include <glfw/glfw3.h>


class GraphicsContextOpenGL : public GraphicsContext
{
public:
    void Init() override;
    void Draw() override;
    void SwapBuffers() override;

    void SetGLFWContext(GLFWwindow* glfwWindow);

    GraphicsContextOpenGL();
    ~GraphicsContextOpenGL();

private:
    GLFWwindow* m_windowHandle = nullptr;
};

