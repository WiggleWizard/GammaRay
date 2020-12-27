#include "grpch.h"
#include "Memory.h"

#include "Tracy.hpp"


uint64_t Memory::memUsage = 0;
uint64_t Memory::maxUsage = 0;

void* Memory::allocStatic(size_t sz)
{
    auto ptr = malloc(sz);

#ifdef GR_PROFILE_MEMORY
    TracyAlloc(ptr, sz);
#endif

    // TODO: Thread safety
    Memory::memUsage += sz;

    return ptr;
}

void* Memory::allocStatic(size_t sz, const char* className)
{
    auto ptr = malloc(sz);

#ifdef GR_PROFILE_MEMORY
    TracyAllocN(ptr, sz, className);
#endif

    // TODO: Thread safety
    Memory::memUsage += sz;

    return ptr;
}

void Memory::freeStatic(void* ptr)
{
    uint8_t* mem = (uint8_t*)ptr;

#ifdef GR_PROFILE_MEMORY
    TracyFree(ptr);
#endif

    // TODO: Thread safety
    uint64_t* s = (uint64_t*)mem;
    Memory::memUsage -= *s;

    free(ptr);
}

void* operator new(size_t sz)
{
    return Memory::allocStatic(sz);
}

void* operator new(size_t sz, const char* className)
{
    return Memory::allocStatic(sz, className);
}

void operator delete(void* ptr) noexcept
{
    Memory::freeStatic(ptr);
}
