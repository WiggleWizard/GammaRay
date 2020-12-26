#pragma once


class Engine
{
    static Engine* singleton;

public:
    static Engine* GetSingleton();

    Engine();
    ~Engine();
};

