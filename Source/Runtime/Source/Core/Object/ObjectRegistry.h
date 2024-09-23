#pragma once

class ObjectRegistry
{
public:
    static ObjectRegistry& Get()
    {
        static ObjectRegistry s;
        return s;
    }

    ObjectRegistry(const ObjectRegistry&) = delete;
    ObjectRegistry& operator =(const ObjectRegistry&) = delete;

    

private:
    ObjectRegistry() {}
    ~ObjectRegistry() {}
};
