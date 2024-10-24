#include "InputManager.h"

#include "InputEvent.h"
#include "Engine/Engine.h"
#include "Windowing/Window.h"
#include "Windowing/WindowManager.h"

#include <imgui.h>
#include <SDL_events.h>

DEFINE_LOGGER_STATIC(LogInputManager, LogVerbosity::Verbose)

void InputManager::PollEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        HandleEvent(&event);
    }
}

void InputManager::HandleEvent(const SDL_Event* event)
{
    windowManagerWeak = GEngine->GetWindowManager();
    auto windowManager = windowManagerWeak.lock();

    CHECK(IsValid(windowManager), "Window Manager invalid, cannot process inputs");

    // Send the event directly to the focused window, in case they wish to preprocess the input
    auto focusedWindow = windowManager->GetFocusedWindow();
    if (IsValid(focusedWindow))
    {
        
        // Don't process mouse specific events for ImGui if relative mouse is enabled
        if (SDL_GetRelativeMouseMode() == SDL_FALSE)
        {
            focusedWindow->ProcessEventForImGui(event);
        }
    }

    // Generate a native input event from SDL events
    ObjectPtr<InputEvent> inputEvent = nullptr;
    bool userGeneratedInput = false;

    auto& io = ImGui::GetIO();
    
    switch (event->type)
    {
    case SDL_WINDOWEVENT:
        windowManager->OnWindowEvent(reinterpret_cast<const SDL_WindowEvent*>(event));
        break;
    case SDL_MOUSEMOTION:
        inputEvent = ProcessMouseMove(reinterpret_cast<const SDL_MouseMotionEvent*>(event));
        userGeneratedInput = true;
        break;
    case SDL_MOUSEWHEEL:
        inputEvent = OnMouseWheel(reinterpret_cast<const SDL_MouseWheelEvent*>(event));
        userGeneratedInput = true;
        break;
    case SDL_MOUSEBUTTONDOWN:
    case SDL_MOUSEBUTTONUP:
        inputEvent = OnMouseButtonPressed(reinterpret_cast<const SDL_MouseButtonEvent*>(event));
        userGeneratedInput = true;
        break;
    case SDL_TEXTINPUT:
        inputEvent = OnTextInput(reinterpret_cast<const SDL_TextInputEvent*>(event));
        userGeneratedInput = true;
        break;
    case SDL_KEYUP:
    case SDL_KEYDOWN:
        inputEvent = OnKeyboardPressed(reinterpret_cast<const SDL_KeyboardEvent*>(event));
        userGeneratedInput = true;
        if (io.WantCaptureKeyboard)
            inputEvent->Handled();
        break;
    case SDL_JOYAXISMOTION:
        inputEvent = OnJoyAxisMotion(reinterpret_cast<const SDL_JoyAxisEvent*>(event));
        userGeneratedInput = true;
        break;
    case SDL_JOYBUTTONDOWN:
    case SDL_JOYBUTTONUP:
        inputEvent = OnJoyButtonPressed(reinterpret_cast<const SDL_JoyButtonEvent*>(event));
        userGeneratedInput = true;
        break;
    default: break;
    }
    
    if (userGeneratedInput && !IsValid(inputEvent))
    {
        LogInputManager.Info("Unknown user generated SDL input {0} (0x{0:X})", event->type);
    }

    if (IsValid(inputEvent))
    {
        if (!inputEvent->HasBeenHandled())
        {
            windowManager->PropagateInputEvent(inputEvent);
        }
    }
}

ObjectPtr<InputEvent> InputManager::ProcessMouseMove(const SDL_MouseMotionEvent* event)
{
    ObjectPtr<InputEventMouseMotion> inputEvent = NewObject<InputEventMouseMotion>();

    inputEvent->position.x = event->x;
    inputEvent->position.y = event->y;
    inputEvent->velocity.x = event->xrel;
    inputEvent->velocity.y = event->yrel;
    
    return inputEvent;
}

ObjectPtr<InputEvent> InputManager::OnMouseButtonPressed(const SDL_MouseButtonEvent* event)
{
    ObjectPtr<InputEventMouseButton> inputEvent = NewObject<InputEventMouseButton>();

    inputEvent->position.x = event->x;
    inputEvent->position.y = event->y;

    inputEvent->pressed = event->state == SDL_PRESSED;
    inputEvent->buttonIndex = event->button;
    
    return inputEvent;
}

ObjectPtr<InputEvent> InputManager::OnMouseWheel(const SDL_MouseWheelEvent* event)
{
    ObjectPtr<InputEventMouseButton> inputEvent;
    return inputEvent;
}

ObjectPtr<InputEvent> InputManager::OnKeyboardPressed(const SDL_KeyboardEvent* event)
{
    ObjectPtr<InputEventKey> inputEvent = NewObject<InputEventKey>();

    inputEvent->pressed = event->type == SDL_KEYDOWN;
    inputEvent->echo = event->repeat > 0;

    inputEvent->keycode = event->keysym.sym;
    inputEvent->scancode = event->keysym.scancode;
    
    return inputEvent;
}

ObjectPtr<InputEvent> InputManager::OnJoyAxisMotion(const SDL_JoyAxisEvent* event)
{
    return nullptr;
}

ObjectPtr<InputEvent> InputManager::OnJoyButtonPressed(const SDL_JoyButtonEvent* event)
{
    return nullptr;
}

ObjectPtr<InputEvent> InputManager::OnTextInput(const SDL_TextInputEvent* event)
{
    return nullptr;
}
