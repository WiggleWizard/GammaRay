#include "grpch.h"
#include "LayerImGui.h"

#include "Core/Debug/ImGuiOpenGLRenderer.h"
#include "Core/Application.h"

#include "glfw/glfw3.h"


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

    // Keyboard mapping. ImGui will use those indices to peek into the io.KeysDown[] array.
    io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
    io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
    io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
    io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
    io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
    io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
    io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
    io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
    io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
    io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
    io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
    io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
    io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
    io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
    io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
    io.KeyMap[ImGuiKey_KeyPadEnter] = GLFW_KEY_KP_ENTER;
    io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
    io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
    io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
    io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
    io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
    io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

    ImGui_ImplOpenGL3_Init(glsl_version);
}


void LayerImGui::OnDetach()
{

}

void LayerImGui::OnProcess()
{
    ImGuiIO& io = ImGui::GetIO();

    Size2i windowSize = Application::GetSingleton()->GetWindowSize();
    io.DisplaySize.x = windowSize.width;
    io.DisplaySize.y = windowSize.height;

    float time = (float)glfwGetTime();
    io.DeltaTime = m_time > 0.f ? (time - m_time) : (1.f / 60.f);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();

    static bool show = true;
    ImGui::ShowDemoWindow(&show);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void LayerImGui::OnEvent(Event& event)
{
    EventDispatcher dispatcher(event);
    dispatcher.Dispatch<EventMouseMoved>(std::bind(&LayerImGui::OnMouseMove, this, std::placeholders::_1));
    dispatcher.Dispatch<EventMousePressed>(std::bind(&LayerImGui::OnMousePressed, this, std::placeholders::_1));
    dispatcher.Dispatch<EventMouseRelease>(std::bind(&LayerImGui::OnMouseRelease, this, std::placeholders::_1));
    dispatcher.Dispatch<EventMouseScrolled>(std::bind(&LayerImGui::OnMouseScrolled, this, std::placeholders::_1));
}

bool LayerImGui::OnMouseMove(EventMouseMoved& event)
{
    ImGuiIO& io = ImGui::GetIO();
    io.MousePos = ImVec2((float)event.GetX(), (float)event.GetY());
    return true;
}

bool LayerImGui::OnMousePressed(EventMousePressed& event)
{
    ImGuiIO& io = ImGui::GetIO();
    io.MouseDown[0] = true;
    return true;
}

bool LayerImGui::OnMouseRelease(EventMouseRelease& event)
{
    ImGuiIO& io = ImGui::GetIO();
    io.MouseDown[0] = false;
    return true;
}

bool LayerImGui::OnMouseScrolled(EventMouseScrolled& event)
{
    ImGuiIO& io = ImGui::GetIO();
    io.MouseWheel = event.GetYOffset();
    return true;
}

