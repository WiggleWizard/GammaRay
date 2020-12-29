#pragma once


class RenderingSystem
{
    static RenderingSystem* m_singleton;

public:
    static RenderingSystem* GetSingleton();

    virtual void Draw() = 0;

    RenderingSystem();
};

// Alias
#define RS RenderingSystem
