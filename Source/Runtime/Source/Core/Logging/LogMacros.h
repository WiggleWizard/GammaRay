#pragma once

#include "LogVerbosity.h"
#include "LoggerCategorized.h"

#define DEFINE_LOGGER_STATIC(CategoryName, DefaultVerbosity) \
    static struct LoggerCategorized##CategoryName : public LoggerCategorized \
    { \
        LoggerCategorized##CategoryName() : LoggerCategorized(#CategoryName, DefaultVerbosity) {} \
    } CategoryName;
