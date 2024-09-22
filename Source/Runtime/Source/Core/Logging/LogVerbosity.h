#pragma once

#include "Core/Types/Types.h"

namespace LogVerbosity
{
    enum Type : unsigned char
    {
        VeryVerbose,
        Verbose,
        LogFile,
        Console,
        Warning,
        Fatal,
    };
}