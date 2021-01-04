#pragma once

#include "InputEvent.h"

#include <glm/glm.hpp>


class GAMMARAY_API Input
{
    static Input* m_singleton;

    typedef void (*EventDispatchFunc)(const InputEvent& event);

public:
    static Input* GetSingleton();

    bool IsKeyPressed(int keycode);
    glm::ivec2 GetMousePosition();
    glm::ivec2 GetMouseVelocity();

private:
    // State trackers
    std::map<int, bool> m_keysPressed; // TODO: Could do with a more optimized type
    glm::ivec2 m_mouseVelocity = {0.f, 0.f};
    glm::ivec2 m_mousePos = {0.f, 0.f};

    uint64_t mouseWindowId = 0;

    EventDispatchFunc m_dispatchFunc = nullptr;

public:
    void ProcessWindowInput(InputEvent& event);

    void RegisterEventCallback(EventDispatchFunc dispatchFunc);

    Input();
    ~Input();
};

