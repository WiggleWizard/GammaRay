#include "grpch.h"
#include "LayerImGui.h"

#include "Core/Application.h"

#include "glfw/glfw3.h"

#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"


LayerImGui::LayerImGui()
    : Layer("ImGui")
{

}

LayerImGui::~LayerImGui()
{

}


void LayerImGui::OnAttach()
{
    const char* glsl_version = "#version 410";

    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

    GLFWwindow* window = static_cast<GLFWwindow*>(Application::GetSingleton()->GetWindow()->GetNativeWindow());

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
}


void LayerImGui::OnDetach()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void LayerImGui::OnProcess()
{
    Begin();
    OnImGuiRender();
    End();
}

void LayerImGui::Begin()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void LayerImGui::End()
{
    ImGuiIO& io = ImGui::GetIO();

    Size2i windowSize = Application::GetSingleton()->GetWindowSize();
    io.DisplaySize.x = (float)windowSize.width;
    io.DisplaySize.y = (float)windowSize.height;

    float time = (float)glfwGetTime();
    io.DeltaTime = m_time > 0.f ? (time - m_time) : (1.f / 60.f);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if(io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow* backupCurrentCtx = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backupCurrentCtx);
    }
}

void LayerImGui::OnImGuiRender()
{
    static bool show = true;
    //ImGui::ShowDemoWindow(&show);
}
