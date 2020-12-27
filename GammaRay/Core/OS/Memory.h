#pragma once


class Memory
{
    static uint64_t memUsage;
    static uint64_t maxUsage;

public:
    static void* allocStatic(size_t sz);
    static void* allocStatic(size_t sz, const char* className);
    static void freeStatic(void* ptr);
};

#define MemNew(m_class) new ( #m_class ) m_class

void* operator new(size_t sz);
void* operator new(size_t sz, const char* className);

void operator delete(void* ptr);
