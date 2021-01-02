#pragma once

#include <glm/glm.hpp>


class Rect2
{
public:
    float x, y;
    float w, h;

    Rect2() {}

    Rect2(float x, float y, float width, float height)
        : x(x), y(y), w(width), h(height)
    {}

    Rect2(float x, float y, float square)
        : x(x), y(y), w(square), h(square)
    {}

    bool intersect(const Rect2& otherRect)
    {
        // TODO: Inline and implement
    }
};
// TODO: Actually implement an int version of Rect2 
typedef Rect2 Rect2i;
