#pragma once

#include "Core/Object/Object.h"

class ObjectRegistry;

class Engine : public Object
{
    //DECLARE_CLASS(Engine, Object)

public:
    Engine();
    ~Engine();

    void Initialize();

private:
};

static ObjectPtr<Engine> GEngine = nullptr;
