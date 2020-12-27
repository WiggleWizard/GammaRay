#pragma once


#define MemNew(m_class) new ( #m_class ) m_class

void* operator new(size_t sz);
void* operator new(size_t sz, const char* className);

void operator delete(void* ptr);
