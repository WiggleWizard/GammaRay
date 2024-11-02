#pragma once

#include "Resource.h"
#include <atomic>

template <typename T>
class Res
{
    static_assert(std::is_base_of<Resource, T>::value, "T must inherit from Resource");

private:
    struct RefCounter
    {
        T* ptr;
        std::atomic<size_t> count;

        explicit RefCounter(T* p) : ptr(p), count(1)
        {
        }

        ~RefCounter()
        {
            if (ptr)
            {
                delete ptr;
            }
        }
    };

public:
    Res() : counter(nullptr)
    {
    }

    // Constructor that takes raw pointer
    explicit Res(T* ptr) : counter(ptr ? new RefCounter(ptr) : nullptr)
    {
        if (counter)
        {
            counter->ptr->Retain();
        }
    }

    // Constructor that takes shared_ptr - converts to raw pointer management
    explicit Res(std::shared_ptr<T> ptr) : counter(ptr ? new RefCounter(ptr.get()) : nullptr)
    {
        if (counter)
        {
            counter->ptr->Retain();
        }
    }

    // Copy constructor
    Res(const Res& other) : counter(other.counter)
    {
        if (counter)
        {
            counter->count++;
            counter->ptr->Retain();
        }
    }

    // Implicit casting
    template <typename U>
    Res(const Res<U>& other)
    {
        // Make the class a friend to access private members
        if (other.counter)
        {
            T* castedPtr = static_cast<T*>(other.counter->ptr);
            if (castedPtr)
            {
                // Share the reference counter instead of creating a new one
                counter = reinterpret_cast<RefCounter*>(other.counter);
                counter->count++;
                counter->ptr->Retain();
            }
            else
            {
                counter = nullptr;
            }
        }
        else
        {
            counter = nullptr;
        }
    }

    // Move constructor
    Res(Res&& other) noexcept : counter(other.counter)
    {
        other.counter = nullptr;
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
            counter = other.counter;
            if (counter)
            {
                counter->count++;
                counter->ptr->Retain();
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
            counter = other.counter;
            other.counter = nullptr;
        }
        return *this;
    }

    // Explicit casting
    template <typename U>
    Res<U> Cast() const
    {
        if (!counter) return Res<U>();

        U* castedPtr = dynamic_cast<U*>(counter->ptr);
        if (castedPtr)
        {
            return Res<U>(castedPtr);
        }

        return Res<U>();
    }

    // Release current resource
    void Release()
    {
        if (counter)
        {
            counter->ptr->Release();
            if (--counter->count == 0)
            {
                delete counter;
            }
            counter = nullptr;
        }
    }

    // Reset with new resource
    void Reset(T* ptr = nullptr)
    {
        Release();
        if (ptr)
        {
            counter = new RefCounter(ptr);
            counter->ptr->Retain();
        }
    }

    // Get current reference count (for debugging/testing)
    size_t GetRefCount() const
    {
        return counter ? counter->count.load() : 0;
    }

    // Accessor operators
    T* operator->() const { return counter ? counter->ptr : nullptr; }
    T& operator*() const { return *counter->ptr; }

    // Utility functions
    bool IsValid() const { return counter != nullptr && counter->ptr != nullptr; }
    T* Get() const { return counter ? counter->ptr : nullptr; }

    // Cast operator to check if resource exists
    explicit operator bool() const { return IsValid(); }

    // Comparison operators
    bool operator==(const Res& other) const { return counter == other.counter; }
    bool operator!=(const Res& other) const { return counter != other.counter; }
    bool operator==(std::nullptr_t) const { return !IsValid(); }
    bool operator!=(std::nullptr_t) const { return IsValid(); }

    RefCounter* counter;
};
