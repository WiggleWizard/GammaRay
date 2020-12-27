#pragma once

#include <string>
#include <sstream>

#include "spdlog/spdlog.h"


enum class EventType
{
    None = 0,
    WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
    KeyPressed, KeyReleased,
    MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
};

enum EventCategory
{
    None = 0,
    EventCategoryApplication = BIT(0),
    EventCategoryInput       = BIT(1),
    EventCategoryKeyboard    = BIT(2),
    EventCategoryMouse       = BIT(3),
    EventCategoryMouseButton = BIT(4)
};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
                               virtual EventType GetEventType() const override { return GetStaticType(); }\
                               virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

class Event
{
    friend class EventDispatcher;

public:
    virtual EventType GetEventType() const = 0;
    virtual const char* GetName() const = 0;
    virtual int GetCategoryFlags() const = 0;
    virtual std::string ToString() const { return GetName(); }

    inline bool IsInCategory(EventCategory category)
    {
        return GetCategoryFlags() & category;
    }

    _FORCE_INLINE_ bool HasBeenHandled() { return m_handled; }

protected:
    bool m_handled = false;
};

class EventDispatcher
{
    template<typename T>
    using EventFn = std::function<bool(T&)>;

public:
    EventDispatcher(Event& event)
        : m_event(event)
    {}

    template<typename T>
    bool Dispatch(EventFn<T> func)
    {
        if(m_event.GetEventType() == T::GetStaticType())
        {
            m_event.m_handled = func(*(T*)&m_event);
            return true;
        }
        return false;
    }

private:
    Event& m_event;
};

#define FMT_EVENT_FORMATTER(type) \
template <> \
struct fmt::formatter<type> \
{ \
    constexpr auto parse(format_parse_context& ctx) { return ctx.end(); } \
    template <typename Context> \
    auto format(const type& e, Context& ctx) { \
        return format_to(ctx.out(), "[{}]", e.ToString()); \
    } \
}; \

FMT_EVENT_FORMATTER(Event)
