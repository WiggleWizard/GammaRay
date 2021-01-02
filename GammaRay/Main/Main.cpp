#include "grpch.h"
#include "Main.h"

#include "Core/Input/Input.h"
#include "Core/MainLoop.h"
#include "Core/OS.h"
#include "Core/Engine.h"
#include "Core/Application.h"
#include "Core/Debug/Log.h"

#include "Core/Event/EventMouse.h"


static std::unique_ptr<Input> input = nullptr;

Engine* Main::m_engine = nullptr;

std::unique_ptr<MainLoop> Main::m_mainLoop       = nullptr;
std::unique_ptr<Application> Main::m_application = nullptr;

std::unique_ptr<SceneServer> Main::m_sceneServer = nullptr;
std::unique_ptr<RenderServer> Main::m_renderServer = nullptr;

uint32_t Main::frame = 0;


void Main::Setup(int argc, char *argv[])
{
    Log::Init();

    m_sceneServer = std::make_unique<SceneServer>();

    m_engine = new Engine();
    input = std::make_unique<Input>();
}

bool Main::Start()
{
    m_mainLoop = std::make_unique<MainLoop>();
    m_renderServer = std::make_unique<RenderServer>();

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
    return true;
}
