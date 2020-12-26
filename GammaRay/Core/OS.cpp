#include "grpch.h"
#include "OS.h"


OS* OS::m_singleton = nullptr;

OS::OS()
{
    m_singleton = this;
}

OS::~OS()
{
    m_singleton = nullptr;
}

OS* OS::GetSingleton()
{
    return m_singleton;
}
