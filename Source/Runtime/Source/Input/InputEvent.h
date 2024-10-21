#pragma once

#include <SDL_keycode.h>
#include <SDL_scancode.h>

class InputEvent : public Object
{
public:
    bool handled = false;
};

class InputEventKey : public InputEvent
{
public:
    bool pressed;
    bool echo;
    
    SDL_Scancode scancode;
    SDL_Keycode keycode;
};

class InputEventMouse : public InputEvent
{
public:
    // Position of the cursor relative to the top left of the window it's in
    Dg::int2 position;
};

class InputEventMouseButton : public InputEventMouse
{
public:
    bool pressed;
    uint8 buttonIndex;
};

class InputEventMouseMotion : public InputEventMouse
{
public:
    Dg::int2 velocity;
};