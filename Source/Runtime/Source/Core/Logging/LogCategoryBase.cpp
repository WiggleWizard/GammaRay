#include "LogCategoryBase.h"

LogCategoryBase::LogCategoryBase(const StringName& categoryName, LogVerbosity::Type defaultVerbosity)
    : name(categoryName)
    , defaultVerbosity(defaultVerbosity)
{
}
