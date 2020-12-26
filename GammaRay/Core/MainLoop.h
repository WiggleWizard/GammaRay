#pragma once

#include "Debug/Profiling.h"


class MainLoop
{
public:
    virtual bool OnProcess(float DeltaTimeMS);
};

