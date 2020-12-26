#pragma once

#include "Core/Core.h"
#include "Event.h"


class GAMMARAY_API EventKey : public Event
{
public:
    EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

    inline int GetKeyCode() const { return m_keyCode; }

protected:
    EventKey(int keyCode)
        : m_keyCode(keyCode)
    {}

    int m_keyCode = 0;
};

class GAMMARAY_API EventKeyPressed : public EventKey
{
public:
    EVENT_CLASS_TYPE(KeyPressed)

    EventKeyPressed(int keyCode, int repeatCount)
        : EventKey(keyCode)
        , m_repeatCount(repeatCount)
    {}

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "EventKeyPressed: " << m_keyCode;
        return ss.str();
    }

private:
    int m_repeatCount = 0;
};

class GAMMARAY_API EventKeyReleased : public EventKey
{
public:
    EVENT_CLASS_TYPE(KeyReleased)

    EventKeyReleased(int keyCode, int repeatCount = 0)
        : EventKey(keyCode)
    {}

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "EventKeyReleased: " << m_keyCode;
        return ss.str();
    }
};
