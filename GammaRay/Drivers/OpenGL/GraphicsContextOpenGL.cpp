#include "grpch.h"
#include "GraphicsContextOpenGL.h"

#include <glad/glad.h>


void GraphicsContextOpenGL::Init()
{
    GR_CORE_ASSERT(m_windowHandle, "Internal window handle not set. Call SetGLFWContext method before initializing");

    glfwMakeContextCurrent(m_windowHandle);

    int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    GR_CORE_ASSERT(status, "glad failed to load");
}

void GraphicsContextOpenGL::Draw()
{

}

void GraphicsContextOpenGL::SwapBuffers()
{
    glfwSwapBuffers(m_windowHandle);
}

void GraphicsContextOpenGL::SetGLFWContext(GLFWwindow* glfwWindow)
{
    GR_CORE_ASSERT(glfwWindow, "Null window handle");
    m_windowHandle = glfwWindow;
}

GraphicsContextOpenGL::GraphicsContextOpenGL()
{

}

GraphicsContextOpenGL::~GraphicsContextOpenGL()
{

}
