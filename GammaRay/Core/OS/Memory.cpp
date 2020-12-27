#include "grpch.h"
#include "Memory.h"

#include "Tracy.hpp"


void* operator new(size_t sz)
{
    auto ptr = malloc(sz);

#ifdef GR_PROFILE_MEMORY
    TracyAlloc(ptr, sz);
#endif

    return ptr;
}

void* operator new(size_t sz, const char* className)
{
    auto ptr = malloc(sz);

#ifdef GR_PROFILE_MEMORY
    TracyAllocN(ptr, sz, className);
#endif

    return ptr;
}

void operator delete(void* ptr) noexcept
{
#ifdef GR_PROFILE_MEMORY
    TracyFree(ptr);
#endif

    free(ptr);
}
