#include "grpch.h"

#include "Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"


std::shared_ptr<spdlog::logger> Log::m_coreLogger;
std::shared_ptr<spdlog::logger> Log::m_clientLogger;


void Log::Init()
{
    spdlog::set_pattern("%^[%T] %n: %v%$");
    m_coreLogger = spdlog::stdout_color_mt("GammaRay");
    m_coreLogger->set_level(spdlog::level::trace);

    m_clientLogger = spdlog::stdout_color_mt("Application");
    m_clientLogger->set_level(spdlog::level::trace);

    GR_CORE_INFO("Log system started");
}
