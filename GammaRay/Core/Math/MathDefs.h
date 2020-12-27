#pragma once


#define MATH_PI 3.1415926535897932384626433833

// Allow floating point numbers to have larger mantissa and exponent, which
// gives floating point maths some more precision.
#ifdef REAL_T_IS_DOUBLE
    typedef double real_t;
#else
    typedef float real_t;
#endif
