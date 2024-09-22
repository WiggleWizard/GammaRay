#pragma once

#include "LogVerbosity.h"
#include "LogCategoryBase.h"
#include "StructuredLogging.h"

#define DEFINE_LOG_CATEGORY_STATIC(CategoryName, DefaultVerbosity) \
    static struct LogCategory##CategoryName : public LogCategoryBase \
    { \
        LogCategory##CategoryName() : LogCategoryBase(#CategoryName, DefaultVerbosity) {} \
    } CategoryName;