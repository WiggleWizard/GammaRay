#pragma once
#include <SDL_events.h>

class InputEvent;
class WindowManager;

union SDL_Event;
struct SDL_WindowEvent;
struct SDL_KeyboardEvent;
struct SDL_MouseMotionEvent;
struct SDL_MouseButtonEvent;
struct SDL_MouseWheelEvent;
struct SDL_JoyAxisEvent;
struct SDL_JoyButtonEvent;
struct SDL_TextInputEvent;

class InputManager : public Object
{
public:
    void PollEvents();
    
    void HandleEvent(const SDL_Event* event);

protected:
    ObjectPtr<InputEvent> ProcessMouseMove(const SDL_MouseMotionEvent* event);
    ObjectPtr<InputEvent> OnMouseButtonPressed(const SDL_MouseButtonEvent* event);
    ObjectPtr<InputEvent> OnMouseWheel(const SDL_MouseWheelEvent* event);
    ObjectPtr<InputEvent> OnKeyboardPressed(const SDL_KeyboardEvent* event);
    ObjectPtr<InputEvent> OnJoyAxisMotion(const SDL_JoyAxisEvent* event);
    ObjectPtr<InputEvent> OnJoyButtonPressed(const SDL_JoyButtonEvent* event);
    ObjectPtr<InputEvent> OnTextInput(const SDL_TextInputEvent* event);

    WeakObjectPtr<WindowManager> windowManagerWeak;
};
