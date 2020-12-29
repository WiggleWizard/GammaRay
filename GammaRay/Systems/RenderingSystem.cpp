#include "grpch.h"
#include "RenderingSystem.h"


RenderingSystem* RenderingSystem::m_singleton = nullptr;

RenderingSystem* RenderingSystem::GetSingleton()
{
    return m_singleton;
}

RenderingSystem::RenderingSystem()
{
    m_singleton = this;
}
