#pragma once

#include "Core/Core.h"
#include "Event.h"

#include <sstream>


FMT_EVENT_FORMATTER(class EventMouseMoved)

class GAMMARAY_API EventMouseMoved : public Event
{
public:
    EVENT_CLASS_TYPE(MouseMoved)
    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

    EventMouseMoved(float x, float y)
        : m_mouseX(x)
        , m_mouseY(y)
    {}

    inline float GetX() const { return m_mouseX; }
    inline float GetY() const { return m_mouseY; }

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "MouseMovedEvent: " << m_mouseX << ", " << m_mouseY;
        return ss.str();
    }

private:
    float m_mouseX, m_mouseY = 0;
};

