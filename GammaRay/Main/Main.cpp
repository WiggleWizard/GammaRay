#include "grpch.h"
#include "Main.h"

#include "Core/Input/Input.h"
#include "Core/MainLoop.h"
#include "Core/OS.h"
#include "Core/Engine.h"
#include "Core/Application.h"
#include "Core/Debug/Log.h"

#include "Core/Event/EventMouse.h"

#include "Systems/RenderingSystem.h"
#include "Systems/RenderingSystem/RenderingSystemDefault.h"


static std::unique_ptr<Input> input = nullptr;
static std::unique_ptr<RenderingSystem> renderingSystem = nullptr;

Engine* Main::m_engine = nullptr;

std::unique_ptr<MainLoop> Main::m_mainLoop       = nullptr;
std::unique_ptr<Application> Main::m_application = nullptr;

uint32_t Main::frame = 0;


void Main::Setup(int argc, char *argv[])
{
    Log::Init();

    m_engine = new Engine();
    input = std::make_unique<Input>();
    renderingSystem = std::make_unique<RenderingSystemDefault>();
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

    RS::GetSingleton()->Draw();

    return mainLoopOk;
}

bool Main::Shutdown()
{
    delete m_engine;
    m_engine = nullptr;
    return true;
}
