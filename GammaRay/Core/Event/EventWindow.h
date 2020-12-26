#pragma once

#include "Core/Core.h"
#include "Event.h"


class GAMMARAY_API EventWindowResize : public Event
{
public:
    EVENT_CLASS_TYPE(WindowResize)
    EVENT_CLASS_CATEGORY(EventCategoryApplication)

    EventWindowResize(unsigned int w, unsigned int h)
        : m_width(w), m_height(h)
    {}

    inline unsigned int GetWidth() const { return m_width; }
    inline unsigned int GetHeight() const { return m_height; }

protected:
    unsigned int m_width, m_height;
};

class GAMMARAY_API EventWindowClose : public Event
{
public:
    EVENT_CLASS_TYPE(WindowClose)
    EVENT_CLASS_CATEGORY(EventCategoryApplication)

    EventWindowClose() {}
};
