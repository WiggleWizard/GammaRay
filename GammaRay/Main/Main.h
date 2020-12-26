#pragma once

#include "Core/Core.h"
#include "Core/Typedefs.h"

#include "Core/Application.h"


/**
 * The absolute core of the engine. There is where everything's initialized correctly and sent off.
 */
class GAMMARAY_API Main
{
    static uint32_t frame;

public:
    // TODO: Error type return
    static void Setup(int argc, char *argv[]);
    static void SetApplicationInstance(Application* applicationInstance) { m_application = std::unique_ptr<Application>(applicationInstance); };
    static bool Start();
    static bool OnProcess();
    static bool Shutdown();

private:
    // Merely a throwaway, we don't technically reach in and use this pointer directly as the
    // process of making a new application creates a singleton. But this is here for safety.
    static std::unique_ptr<Application> m_application;
    static std::unique_ptr<MainLoop> m_mainLoop;
    static Engine* m_engine;
};

