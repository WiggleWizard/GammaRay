#pragma once

class ImGuiComponent : public Object
{
public:
    ImGuiComponent() = default;
    virtual ~ImGuiComponent() = default;
    
    virtual void Draw() {}
};
