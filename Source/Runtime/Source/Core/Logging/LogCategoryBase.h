#pragma once

#include "LogVerbosity.h"
#include "Core/Types/StringName.h"

struct LogCategoryBase
{
    LogCategoryBase(const StringName& categoryName, LogVerbosity::Type defaultVerbosity);
    
    StringName name = "";
    LogVerbosity::Type defaultVerbosity;
};
