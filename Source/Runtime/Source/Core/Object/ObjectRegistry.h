#pragma once

#include "Object.h"
#include "ObjectPtr.h"

#include <typeindex>

class ObjectRegistry : public Object
{
public:
    static ObjectRegistry& Get()
    {
        static ObjectRegistry s;
        return s;
    }

public:
    ObjectRegistry(const ObjectRegistry&) = delete;
    ObjectRegistry& operator =(const ObjectRegistry&) = delete;
    
private:
    ObjectRegistry() {}
    ~ObjectRegistry() {}
    
public:
    template <typename T, typename... Args>
    ObjectPtr<T> CreateObject(Args&&... args)
    {
        // If compilation failed here, check to ensure that the object you're trying to create
        // inherits from `Object`.
        static_assert(std::is_base_of_v<Object, T>, "T must inherit from Object");
        
        return ObjectPtr<T>(new T(args...));
    }
};