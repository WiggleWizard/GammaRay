#pragma once

union SDL_Event;

class InputManager : public Object
{
public:
    void HandleEvent(const SDL_Event* event);
};
