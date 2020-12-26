#pragma once


struct Color
{
    float r = 0.f;
    float g = 0.f;
    float b = 0.f;
    float a = 1.f;

    Color(float grey)
        : r(grey), g(grey), b(grey), a(1.f)
    {}

    Color() : Color(0) {}

    Color(float r, float g, float b)
        : r(r), g(g), b(b), a(1.f)
    {}
};
