#pragma once

#include "Resources/ResPath.h"
#include "UI/ImGuiComponent.h"

#include <filesystem>

class ImGuiComponentFileBrowser : public ImGuiComponent
{
public:
    void Draw() override;

protected:
    ResPath currentDir = "/Editor/Materials";
};
