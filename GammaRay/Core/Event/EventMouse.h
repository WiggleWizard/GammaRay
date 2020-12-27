#pragma once

#include "Core/Core.h"
#include "Event.h"

#include <sstream>


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

class GAMMARAY_API EventMouseScrolled : public Event
{
public:
    EVENT_CLASS_TYPE(MouseScrolled)
    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

    EventMouseScrolled(float xOffset, float yOffset)
        : m_xOffset(xOffset)
        , m_yOffset(yOffset)
    {}

    inline float GetXOffset() const { return m_xOffset; }
    inline float GetYOffset() const { return m_yOffset; }

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "EventMouseScrolled: " << m_xOffset << ", " << m_yOffset;
        return ss.str();
    }

protected:
    float m_xOffset, m_yOffset;
};

class GAMMARAY_API EventMousePressed : public Event
{
public:
    EVENT_CLASS_TYPE(MouseButtonPressed)
    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

    EventMousePressed(int button) : m_button(button) {}

    inline int GetButton() const { return m_button; }

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "EventMousePressed: " << m_button;
        return ss.str();
    }

protected:
    int m_button = 0;
};

class GAMMARAY_API EventMouseRelease : public Event
{
public:
    EVENT_CLASS_TYPE(MouseButtonReleased)
    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

    EventMouseRelease(int button) : m_button(button) {}

    inline int GetButton() const { return m_button; }

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "EventMouseReleased: " << m_button;
        return ss.str();
    }

protected:
    int m_button = 0;
};
