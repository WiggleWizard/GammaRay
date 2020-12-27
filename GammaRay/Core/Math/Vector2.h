#pragma once

#include "Core/Core.h"
#include "Core/Math/MathDefs.h"


struct Vector2
{
    union
    {
        real_t x = 0;
        real_t width;
    };

    union
    {
        real_t y = 0;
        real_t height;
    };

    _FORCE_INLINE_ Vector2() {}
    _FORCE_INLINE_ Vector2(real_t x, real_t y) : x(x), y(y) {}

    /**
     * Allow components to be referenced with square bracket notation.
     */
    _FORCE_INLINE_ real_t &operator[](int i) { return i ? x : y; }
    _FORCE_INLINE_ const real_t& operator[](int i) const { return i ? x : y; }
};
typedef Vector2 Size2;
typedef Vector2 Point2;


struct Vector2i
{
    union
    {
        int x = 0;
        int width;
    };

    union
    {
        int y = 0;
        int height;
    };

    _FORCE_INLINE_ Vector2i() {}
    _FORCE_INLINE_ Vector2i(int x, int y) : x(x), y(y) {}

    /**
     * Allow components to be referenced with square bracket notation.
     */
    _FORCE_INLINE_ int &operator[](int i) { return i ? x : y; }
    _FORCE_INLINE_ const int& operator[](int i) const { return i ? x : y; }
};
typedef Vector2i Size2i;
typedef Vector2i Point2i;
