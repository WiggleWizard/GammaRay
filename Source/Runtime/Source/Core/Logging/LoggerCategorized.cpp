#include "LoggerCategorized.h"

LoggerCategorized::LoggerCategorized(const StringName& categoryName, LogVerbosity::Type defaultVerbosity)
    : name(categoryName)
    , defaultVerbosity(defaultVerbosity)
{
    spdlogLogger = spdlog::default_logger()->clone(categoryName.GetString());
    spdlog::register_logger(spdlogLogger);
}
