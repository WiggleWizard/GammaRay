#pragma once

class EngineModule
{
public:
    void PreEngineInit();
    void EngineInitialized();

    virtual void OnPreEngineInit() {}
    virtual void OnEngineInitialized() {}
};
