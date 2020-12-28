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

void Input::ProcessWindowInput(InputEvent& event)
{
    InputEventKey* eventKey = Object::CastTo<InputEventKey>(&event);
    if(eventKey)
    {
        m_keysPressed.insert_or_assign(eventKey->keycode, eventKey->pressed);
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
