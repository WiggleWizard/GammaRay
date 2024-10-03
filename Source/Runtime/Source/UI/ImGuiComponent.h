#pragma once

class ImGuiComponent
{
public:
    ImGuiComponent() = default;
    virtual ~ImGuiComponent() = default;
    
    virtual void Draw() {}
};
