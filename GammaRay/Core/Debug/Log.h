#pragma once

#include "Core/Core.h"

#include "spdlog/spdlog.h"


class GAMMARAY_API Log
{
public:
    static void Init();

    inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return m_coreLogger; }
    inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return m_clientLogger; }

private:
    static std::shared_ptr<spdlog::logger> m_coreLogger;
    static std::shared_ptr<spdlog::logger> m_clientLogger;
};

#define GR_CORE_ERROR(...)      Log::GetCoreLogger()->error(__VA_ARGS__);
#define GR_CORE_WARN(...)       Log::GetCoreLogger()->warn(__VA_ARGS__);
#define GR_CORE_INFO(...)       Log::GetCoreLogger()->info(__VA_ARGS__);
#define GR_CORE_TRACE(...)      Log::GetCoreLogger()->trace(__VA_ARGS__);

#define GR_CLIENT_ERROR(...)    Log::GetClientLogger()->error(__VA_ARGS__);
#define GR_CLIENT_WARN(...)     Log::GetClientLogger()->warn(__VA_ARGS__);
#define GR_CLIENT_INFO(...)     Log::GetClientLogger()->info(__VA_ARGS__);
#define GR_CLIENT_TRACE(...)    Log::GetClientLogger()->trace(__VA_ARGS__);
