#include "grpch.h"
#include "GraphicsContextOpenGL3.h"

#include <glad/glad.h>


void GraphicsContextOpenGL3::Init()
{
    GR_CORE_ASSERT(m_windowHandle, "Internal window handle not set. Call SetGLFWContext method before initializing");

    glfwMakeContextCurrent(m_windowHandle);

    int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    GR_CORE_ASSERT(status, "glad failed to load");
}

void GraphicsContextOpenGL3::Draw()
{

}

void GraphicsContextOpenGL3::SwapBuffers()
{
    glfwSwapBuffers(m_windowHandle);
}

void GraphicsContextOpenGL3::SetGLFWContext(GLFWwindow* glfwWindow)
{
    GR_CORE_ASSERT(glfwWindow, "Null window handle");
    m_windowHandle = glfwWindow;
}

GraphicsContextOpenGL3::GraphicsContextOpenGL3()
{

}

GraphicsContextOpenGL3::~GraphicsContextOpenGL3()
{

}
