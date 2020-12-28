#pragma once

#include "InputEvent.h"


class GAMMARAY_API Input
{
    static Input* m_singleton;

    typedef void (*EventDispatchFunc)(const InputEvent& event);

public:
    static Input* GetSingleton();

    bool IsKeyPressed(int keycode);

private:
    // State trackers
    std::map<int, bool> m_keysPressed; // TODO: Could do with a more optimized type
    Point2i mousePos;
    uint64_t mouseWindowId = 0;

    EventDispatchFunc m_dispatchFunc = nullptr;

public:
    void ProcessWindowInput(InputEvent& event);

    void RegisterEventCallback(EventDispatchFunc dispatchFunc);

    Input();
    ~Input();
};

