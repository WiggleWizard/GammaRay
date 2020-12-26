#include "grpch.h"
#include "Main.h"

#include "Core/MainLoop.h"
#include "Core/OS.h"
#include "Core/Engine.h"
#include "Core/Application.h"
#include "Core/Debug/Log.h"

#include "Core/Event/EventMouse.h"


Engine* m_engine           = nullptr;
MainLoop* m_mainLoop       = nullptr;
Application* m_application = nullptr;

uint32_t Main::frame = 0;


void Main::Setup(int argc, char *argv[])
{
    Log::Init();
    m_engine = new Engine();

}

bool Main::Start()
{
    m_mainLoop = std::make_unique<MainLoop>();

    GR_CORE_TRACE("Main started");

    return true;
}

bool Main::OnProcess()
{
    frame++;

    bool mainLoopOk = m_mainLoop->OnProcess(0);

    return mainLoopOk;
}

bool Main::Shutdown()
{
    delete m_engine;
    m_engine = nullptr;
}
