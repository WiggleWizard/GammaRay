#include "EngineModule.h"

void EngineModule::PreEngineInit()
{
    OnPreEngineInit();
}

void EngineModule::EngineInitialized()
{
    OnEngineInitialized();
}
