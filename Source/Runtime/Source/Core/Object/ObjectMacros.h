#pragma once

#include "Core/Object/ObjectRegistry.h"

#define DECLARE_CLASS(clazz, superClass) \
    private: \
        using Super = superClass; \
    public:

/**
 * Creates a shared pointer.
 */
template<class T, class... Args>
ObjectPtr<T> NewObject(Args&&... args)
{
    return ObjectRegistry::Get().CreateObject<T>(std::forward<Args>(args)...);
}

template<class T>
bool IsValid(ObjectPtr<T>& objectPtr)
{
    return objectPtr != nullptr;
}