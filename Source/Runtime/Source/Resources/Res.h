#pragma once

#include "Resource.h"

template <typename T>
class Res
{
    static_assert(std::is_base_of<Resource, T>::value, "T must inherit from Resource");

public:
    Res() : resource(nullptr)
    {
    }

    // Constructor that takes raw pointer
    explicit Res(T* ptr) : resource(ptr)
    {
        if (resource)
        {
            resource->Retain();
        }
    }

    // Constructor that takes shared_ptr
    explicit Res(std::shared_ptr<T> ptr) : resource(ptr)
    {
        if (resource)
        {
            resource->Retain();
        }
    }

    // Copy constructor
    Res(const Res& other) : resource(other.resource)
    {
        if (resource)
        {
            resource->Retain();
        }
    }

    // Move constructor
    Res(Res&& other) noexcept : resource(std::move(other.resource))
    {
    }

    // Destructor
    ~Res()
    {
        Release();
    }

    // Copy assignment
    Res& operator=(const Res& other)
    {
        if (this != &other)
        {
            Release();
            resource = other.resource;
            if (resource)
            {
                resource->Retain();
            }
        }
        return *this;
    }

    // Move assignment
    Res& operator=(Res&& other) noexcept
    {
        if (this != &other)
        {
            Release();
            resource = std::move(other.resource);
        }
        return *this;
    }

    // Release current resource
    void Release()
    {
        if (resource)
        {
            resource->Release();
            resource.reset();
        }
    }

    // Reset with new resource
    void Reset(T* ptr = nullptr)
    {
        Release();
        resource = std::shared_ptr<T>(ptr);
        if (resource)
        {
            resource->Retain();
        }
    }

    // Accessor operators
    T* operator->() const { return resource.get(); }
    T& operator*() const { return *resource; }

    // Utility functions
    bool IsValid() const { return resource != nullptr; }
    T* Get() const { return resource.get(); }

    // Cast operator to check if resource exists
    explicit operator bool() const { return IsValid(); }

    // Comparison operators
    bool operator==(const Res& other) const { return resource == other.resource; }
    bool operator!=(const Res& other) const { return resource != other.resource; }
    bool operator==(std::nullptr_t) const { return !IsValid(); }
    bool operator!=(std::nullptr_t) const { return IsValid(); }

private:
    std::shared_ptr<T> resource;
};
