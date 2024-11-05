#pragma once

#include "Rendering/WindowViewport.h"

class ImGuiComponentFileBrowser;
class ImGuiComponentViewport;

class EditorWindowViewport : public WindowViewport
{
    DECLARE_CLASS(EditorWindowViewport, WindowViewport)
    
public:
    EditorWindowViewport(Dg::RefCntAutoPtr<Dg::ISwapChain>& swapChain, Dg::RefCntAutoPtr<Dg::IRenderDevice>& renderDevice);

protected:
    void DrawImGui() override;

    bool imguiDemoWindowOpen = true;
    ObjectPtr<ImGuiComponentViewport> imGuiComponentViewport = nullptr;
    ObjectPtr<ImGuiComponentFileBrowser> imGuiComponentFileBrowser = nullptr;
};
