#pragma once


class Timestep
{
public:
    Timestep(float time = 0.f)
        : m_time(time)
    {}

    operator float() const { return m_time; }

    _FORCE_INLINE_ float GetSeconds() const { return m_time; }
    _FORCE_INLINE_ float GetMilliseconds() const { return m_time * 1000.f; }

private:
    float m_time;
};
