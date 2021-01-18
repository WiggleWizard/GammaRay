#include "grpch.h"
#include "LayerImGui.h"

#include "Core/Application.h"
#include "Servers/RenderServer.h"
#include "Servers/SceneServer.h"

#include "Scene/Components/Gameplay/CameraMovement.h"

#include "glfw/glfw3.h"

#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"
#include "imgui/imgui_internal.h"

#define RegWidget(T, funcName) \
RegisterComponentWidgetRenderFunc( \
    entt::type_info<T>().id(), \
    [this](entt::registry& reg, auto e) \
    { \
        auto& t = reg.get<T>(e); \
        this->funcName(&t); \
    } \
);


void LayerImGui::WidgetComponentSceneLink(ComponentSceneLink* c)
{
    ImGui::Text(c->entityName.c_str());
}

void LayerImGui::WidgetComponentTransform3D(ComponentTransform3D* c)
{
    static bool open = true;
    if(ImGui::CollapsingHeader("Transform 3D", &open, ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImGui::InputFloat3("Position", (float*)&c->position);
        ImGui::InputFloat3("Rotation", (float*)&c->rotation);
    }
}

void LayerImGui::WidgetComponentEditorCamera3DMovement(ComponentEditorCamera3DMovement* c)
{
    static bool open = true;
    if(ImGui::CollapsingHeader("Camera Movement", &open, ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImGui::DragFloat("Move Speed", &c->moveSpeed, 0.1f);
    }
}

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

    // Classic HL GUI theme from: https://github.com/ocornut/imgui/issues/707#issuecomment-576867100
    ImVec4* colors = ImGui::GetStyle().Colors;
    colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    colors[ImGuiCol_WindowBg] = ImVec4(0.29f, 0.34f, 0.26f, 1.00f);
    colors[ImGuiCol_ChildBg] = ImVec4(0.29f, 0.34f, 0.26f, 1.00f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.24f, 0.27f, 0.20f, 1.00f);
    colors[ImGuiCol_Border] = ImVec4(0.54f, 0.57f, 0.51f, 0.50f);
    colors[ImGuiCol_BorderShadow] = ImVec4(0.14f, 0.16f, 0.11f, 0.52f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.24f, 0.27f, 0.20f, 1.00f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.27f, 0.30f, 0.23f, 1.00f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.30f, 0.34f, 0.26f, 1.00f);
    colors[ImGuiCol_TitleBg] = ImVec4(0.24f, 0.27f, 0.20f, 1.00f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.29f, 0.34f, 0.26f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
    colors[ImGuiCol_MenuBarBg] = ImVec4(0.24f, 0.27f, 0.20f, 1.00f);
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.35f, 0.42f, 0.31f, 1.00f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.28f, 0.32f, 0.24f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.25f, 0.30f, 0.22f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.23f, 0.27f, 0.21f, 1.00f);
    colors[ImGuiCol_CheckMark] = ImVec4(0.59f, 0.54f, 0.18f, 1.00f);
    colors[ImGuiCol_SliderGrab] = ImVec4(0.35f, 0.42f, 0.31f, 1.00f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.54f, 0.57f, 0.51f, 0.50f);
    colors[ImGuiCol_Button] = ImVec4(0.29f, 0.34f, 0.26f, 0.40f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.35f, 0.42f, 0.31f, 1.00f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.54f, 0.57f, 0.51f, 0.50f);
    colors[ImGuiCol_Header] = ImVec4(0.35f, 0.42f, 0.31f, 1.00f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.35f, 0.42f, 0.31f, 0.6f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.54f, 0.57f, 0.51f, 0.50f);
    colors[ImGuiCol_Separator] = ImVec4(0.14f, 0.16f, 0.11f, 1.00f);
    colors[ImGuiCol_SeparatorHovered] = ImVec4(0.54f, 0.57f, 0.51f, 1.00f);
    colors[ImGuiCol_SeparatorActive] = ImVec4(0.59f, 0.54f, 0.18f, 1.00f);
    colors[ImGuiCol_ResizeGrip] = ImVec4(0.19f, 0.23f, 0.18f, 0.00f); // grip invis
    colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.54f, 0.57f, 0.51f, 1.00f);
    colors[ImGuiCol_ResizeGripActive] = ImVec4(0.59f, 0.54f, 0.18f, 1.00f);
    colors[ImGuiCol_Tab] = ImVec4(0.35f, 0.42f, 0.31f, 1.00f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.54f, 0.57f, 0.51f, 0.78f);
    colors[ImGuiCol_TabActive] = ImVec4(0.59f, 0.54f, 0.18f, 1.00f);
    colors[ImGuiCol_TabUnfocused] = ImVec4(0.24f, 0.27f, 0.20f, 1.00f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.35f, 0.42f, 0.31f, 1.00f);
    colors[ImGuiCol_DockingPreview] = ImVec4(0.59f, 0.54f, 0.18f, 1.00f);
    colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.59f, 0.54f, 0.18f, 1.00f);
    colors[ImGuiCol_PlotHistogram] = ImVec4(1.00f, 0.78f, 0.28f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    colors[ImGuiCol_TextSelectedBg] = ImVec4(0.59f, 0.54f, 0.18f, 1.00f);
    colors[ImGuiCol_DragDropTarget] = ImVec4(0.73f, 0.67f, 0.24f, 1.00f);
    colors[ImGuiCol_NavHighlight] = ImVec4(0.59f, 0.54f, 0.18f, 1.00f);
    colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
    colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
    colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);

    ImGuiStyle& style = ImGui::GetStyle();
    style.FrameBorderSize = 1.0f;
    style.WindowRounding = 0.0f;
    style.ChildRounding = 0.0f;
    style.FrameRounding = 0.0f;
    style.PopupRounding = 0.0f;
    style.ScrollbarRounding = 0.0f;
    style.GrabRounding = 0.0f;
    style.TabRounding = 0.0f;

    ImGuiIO& io = ImGui::GetIO();
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
    //io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

    GLFWwindow* window = static_cast<GLFWwindow*>(Application::GetSingleton()->GetWindow()->GetNativeWindow());

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Render funcs for component widgets in the inspector
    SceneServer* sceneServer = SceneServer::GetSingleton();
    entt::registry& registry = sceneServer->GetRawRegistry();

    // Register widgets for each component
    // TODO: I'm pretty sure this stuff shouldn't be in this class but it will stay here for now until I find a better place for it
    RegWidget(ComponentSceneLink, WidgetComponentSceneLink);
    RegWidget(ComponentTransform3D, WidgetComponentTransform3D);
    RegWidget(ComponentEditorCamera3DMovement, WidgetComponentEditorCamera3DMovement);
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
    io.DisplaySize.x = (float)windowSize.x;
    io.DisplaySize.y = (float)windowSize.y;

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
    const Timestep& frameTimestep = RenderServer::GetSingleton()->GetFrameTime();
    float frameTimeMs = frameTimestep.GetMilliseconds();

    ImGuiIO& io = ImGui::GetIO();

    bool open = true;

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);
    ImGui::SetNextWindowViewport(viewport->ID);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("DockSpace", &open, window_flags);
    ImGui::PopStyleVar();

    ImGui::PopStyleVar(2);

    if(ImGui::DockBuilderGetNode(ImGui::GetID("MyDockspace")) == NULL)
    {
        ImGuiID dockspace_id = ImGui::GetID("MyDockspace");
        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::DockBuilderRemoveNode(dockspace_id); // Clear out existing layout
        ImGui::DockBuilderAddNode(dockspace_id); // Add empty node

        ImGuiID dock_main_id = dockspace_id; // This variable will track the document node, however we are not using it here as we aren't docking anything into it.
        ImGuiID dock_id_left = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Left, 0.20f, NULL, &dock_main_id);
        ImGuiID dock_id_right = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Right, 0.20f, NULL, &dock_main_id);
        ImGuiID dock_id_bottom = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Down, 0.20f, NULL, &dock_main_id);

        ImGui::DockBuilderDockWindow("Scene", dock_id_left);
        ImGui::DockBuilderDockWindow("Renderer", dock_main_id);
        ImGui::DockBuilderDockWindow("Inspector", dock_id_right);
        ImGui::DockBuilderDockWindow("Asset Browser", dock_id_bottom);
        ImGui::DockBuilderFinish(dockspace_id);
    }

    ImGuiID dockspace_id = ImGui::GetID("MyDockspace");
    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), 0);
    ImGui::End();

    SceneServer* sceneServer = SceneServer::GetSingleton();
    entt::registry& registry = sceneServer->GetRawRegistry();

    if(ImGui::Begin("Scene", &open, 0))
    {
        static ImGuiTreeNodeFlags base_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;
        ImGuiTreeNodeFlags node_flags = base_flags;

        const auto& view = registry.view<ComponentSceneLink>();
        for(entt::entity entity : view)
        {
            const ComponentSceneLink& sceneLink = view.get<ComponentSceneLink>(entity);
            node_flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen; // ImGuiTreeNodeFlags_Bullet
            ImGui::TreeNodeEx((void*)(intptr_t)0, node_flags, "%s", sceneLink.entityName.c_str());

            if(ImGui::IsItemClicked())
                m_entitySelected = entity;
        }
    }
    ImGui::End();

    if(ImGui::Begin("Renderer", &open, 0))
    {
        int texId = RenderServer::GetSingleton()->m_texColor->GetRendererId();

        if(m_isControllingCamera == false && io.MouseDown[1] == true && ImGui::IsWindowHovered())
        {
            glfwSetInputMode((GLFWwindow*)Application::GetSingleton()->GetWindow()->GetNativeWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            m_isControllingCamera = true;
        }
        else if(m_isControllingCamera == true && io.MouseDown[1] == false)
        {
            glfwSetInputMode((GLFWwindow*)Application::GetSingleton()->GetWindow()->GetNativeWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            m_isControllingCamera = false;
        }

        if(m_isControllingCamera)
        {
            const auto& view = registry.view<ComponentEditorCamera3DMovement>();
            for(entt::entity entity : view)
            {
                ComponentEditorCamera3DMovement& camera3DMovement = view.get<ComponentEditorCamera3DMovement>(entity);
                camera3DMovement.UpdateRotationAndPosition({io.MouseDelta.x, io.MouseDelta.y}, frameTimestep);
            }
        }

        ImGui::GetWindowDrawList()->AddImage(
            (void*)texId,
            ImVec2(ImGui::GetCursorScreenPos()),
            ImVec2(ImGui::GetCursorScreenPos().x + 800,
                ImGui::GetCursorScreenPos().y + 600), ImVec2(0, 1), ImVec2(1, 0));

        ImGui::Text("FPS: %.0f (%.0f ms/frame)", round(1000.f / frameTimeMs), frameTimeMs);
        ImGui::Text("Draw Calls: %d", RenderServer::GetSingleton()->GetDrawCallCount());
    }
    ImGui::End();

    if(ImGui::Begin("Inspector", &open, 0))
    {
        if(m_entitySelected != entt::null)
        {
            registry.visit(m_entitySelected, [&](auto component)
            {
                auto search = m_inspectorWidgetRenderFuncs.find(component);
                if(search != m_inspectorWidgetRenderFuncs.end())
                {
                    search->second(registry, m_entitySelected);
                }
            });
        }
    }
    ImGui::End();

    ImGui::Begin("Asset Browser", &open, 0);
    ImGui::End();
}
