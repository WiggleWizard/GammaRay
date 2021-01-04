#include "grpch.h"
#include "Input.h"


Input* Input::m_singleton = nullptr;

Input* Input::GetSingleton()
{
    return m_singleton;
}

bool Input::IsKeyPressed(int keycode)
{
    const auto& it = m_keysPressed.find(keycode);
    if(it != m_keysPressed.end())
        return it->second;
    return false;
}

glm::ivec2 Input::GetMousePosition()
{
    return m_mousePos;
}

glm::ivec2 Input::GetMouseVelocity()
{
    // TODO: Currently broken because it's only calculated when a new event arrives.
    //       For now the developer needs to calculate this manually in their code.
    return m_mouseVelocity;
}

void Input::ProcessWindowInput(InputEvent& event)
{
    InputEventKey* eventKey = Object::CastTo<InputEventKey>(&event);
    if(eventKey)
    {
        m_keysPressed.insert_or_assign(eventKey->keycode, eventKey->pressed);
    }

    m_mouseVelocity = {0.f, 0.f};
    InputEventMouseMotion* eventMouseMotion = Object::CastTo<InputEventMouseMotion>(&event);
    if(eventMouseMotion)
    {
        m_mouseVelocity = eventMouseMotion->position - m_mousePos;
        m_mousePos = eventMouseMotion->position;
    }

    if(m_dispatchFunc)
        m_dispatchFunc(event);
}

void Input::RegisterEventCallback(EventDispatchFunc dispatchFunc)
{
    m_dispatchFunc = dispatchFunc;
}

Input::Input()
{
    m_singleton = this;
}

Input::~Input()
{

}
