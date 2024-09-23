#pragma once

class EngineModule;

class Engine : public Object
{
    DECLARE_CLASS(Engine, Object)
    
public:
    Engine(const Engine&) = delete;
    Engine& operator =(const Engine&) = delete;

private:
    Engine() {}
    ~Engine() {}

    std::vector<EngineModule*> modules;
};

static Engine* GEngine = nullptr;
