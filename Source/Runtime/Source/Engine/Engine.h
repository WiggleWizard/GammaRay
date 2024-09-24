#pragma once

#include "Core/Object/Object.h"

class WindowManager;
class ObjectRegistry;

class Engine : public Object
{
    DECLARE_CLASS(Engine, Object)

public:
    Engine();
    ~Engine();

    void Initialize();

private:
    ObjectPtr<WindowManager> windowManager = nullptr;
};

static ObjectPtr<Engine> GEngine = nullptr;
