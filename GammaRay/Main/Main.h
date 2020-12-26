#pragma once

#include "Core/Core.h"
#include "Core/Typedefs.h"


class GAMMARAY_API Main
{
    static uint32_t frame;

public:
    // TODO: Error type return
    static void Setup(int argc, char *argv[]);
    static bool Start();

    static bool OnProcess();
};

