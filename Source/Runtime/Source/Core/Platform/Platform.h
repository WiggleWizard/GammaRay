#pragma once

typedef unsigned char 		uint8;
typedef unsigned short int	uint16;
typedef unsigned int		uint32;
typedef unsigned long long	uint64;

typedef	signed char			int8;
typedef signed short int	int16;
typedef signed int	 		int32;
typedef signed long long	int64;

#include <cassert>

#if defined(_MSC_VER)
    #define DEBUG_BREAK() __debugbreak()
#elif defined(__clang__) || defined(__GNUC__)
    #define DEBUG_BREAK() __builtin_trap()
#else
    #define DEBUG_BREAK() assert(false)
#endif

// Basic assertion that breaks in debug, disabled in release
#ifdef NDEBUG
    #define CHECK(condition) ((void)0)
#else
    #define CHECK(condition) \
        do { \
            if (!(condition)) { \
                DEBUG_BREAK(); \
            } \
        } while(0)
#endif

// Assertion that breaks in debug and returns a value
#ifdef NDEBUG
    #define CHECK_RETURN(condition, return_value) \
        do { \
            if (!(condition)) { \
                return (return_value); \
            } \
        } while(0)
#else
    #define CHECK_RETURN(condition, return_value) \
        do { \
            if (!(condition)) { \
                DEBUG_BREAK(); \
                return (return_value); \
            } \
        } while(0)
#endif

// Assertion that breaks in debug and returns void
#ifdef NDEBUG
    #define CHECK_RETURN_VOID(condition) \
        do { \
            if (!(condition)) { \
                return; \
            } \
        } while(0)
#else
    #define CHECK_RETURN_VOID(condition) \
        do { \
            if (!(condition)) { \
                DEBUG_BREAK(); \
                return; \
            } \
        } while(0)
#endif