#pragma once

#include "Debug/Profiling.h"

class MainLoop
{
public:
    virtual void Step(float DeltaTimeMS);
};

