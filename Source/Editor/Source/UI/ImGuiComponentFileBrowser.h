#pragma once

#include "UI/ImGuiComponent.h"

#include <filesystem>

class ImGuiComponentFileBrowser : public ImGuiComponent
{
public:
    void Draw() override;

protected:
    std::filesystem::path currentDir = "/Editor/Materials";
};
