#pragma once

#include "LogVerbosity.h"
#include "Core/Types/StringName.h"

#include <spdlog/spdlog.h>

struct LoggerCategorized
{
    LoggerCategorized(const StringName& categoryName, LogVerbosity::Type defaultVerbosity);

    template<class... Args>
    void Info(spdlog::format_string_t<Args...> fmt, Args... args)
    {
        spdlogLogger->info(fmt, std::forward<Args>(args)...);
    }

    template<class... Args>
    void Warn(spdlog::format_string_t<Args...> fmt, Args... args)
    {
        spdlogLogger->warn(fmt, std::forward<Args>(args)...);
    }

    template<class... Args>
    void Error(spdlog::format_string_t<Args...> fmt, Args... args)
    {
        spdlogLogger->error(fmt, std::forward<Args>(args)...);
    }

    template<class... Args>
    void Critical(spdlog::format_string_t<Args...> fmt, Args... args)
    {
        spdlogLogger->critical(fmt, std::forward<Args>(args)...);
    }

private:
    StringName name = "";
    LogVerbosity::Type defaultVerbosity;
    std::shared_ptr<spdlog::logger> spdlogLogger = nullptr;
};
