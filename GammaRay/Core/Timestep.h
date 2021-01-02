#pragma once


class Timestep
{
public:
    Timestep(float time = 0.f)
        : m_time(time)
    {}

    operator float() const { return m_time; }

    float GetSeconds() const { return m_time; }
    float GetMilliseconds() const { return m_time * 1000.f; }

private:
    float m_time;
};
