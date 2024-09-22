#pragma once

#include "Core/Logging/LogCategoryBase.h"

#include <spdlog/spdlog.h>

struct Logging
{
    template<class... Args>
    static void BasicLog(const LogCategoryBase& Category, spdlog::format_string_t<Args...> fmt, Args... args)
    {
        spdlog::info(fmt, std::forward<Args>(args)...);
    }
};

