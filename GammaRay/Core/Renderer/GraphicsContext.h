#pragma once


class GraphicsContext
{
public:
    virtual void Init() = 0;
    virtual void Draw() = 0;
    virtual void SwapBuffers() = 0;

    GraphicsContext() {};
    virtual ~GraphicsContext() {};
};

