#pragma once

class EngineModule
{
public:
    void PreEngineInit();

    virtual void OnPreEngineInit() {}
};
