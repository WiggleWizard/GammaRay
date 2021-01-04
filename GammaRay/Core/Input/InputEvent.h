#pragma once

#include <glm/glm.hpp>


class InputEvent : public Object
{
    GRCLASS(InputEvent, Object)
};

class InputEventFromWindow : public InputEvent
{
public:
    WindowID windowId = 0;
};

class InputEventWithModifiers : public InputEventFromWindow
{
    bool shift = false;
    bool alt   = false;
    bool ctrl  = false;
    bool meta  = false;
};

class InputEventKey : public InputEventWithModifiers
{
public:
    bool pressed = false;
    uint32_t keycode = 0;
    bool echo = false; // Is a repeated key (user holding it down)
};

class InputEventMouse : public InputEventWithModifiers
{
public:
    glm::ivec2 position;
};

class InputEventMouseButton : public InputEventMouse
{
public:
    bool pressed = false;
    int buttonIndex = 0;
};

class InputEventMouseMotion : public InputEventMouse
{
    
};
