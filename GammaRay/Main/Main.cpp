#include "grpch.h"
#include "Main.h"

#include "Core/MainLoop.h"
#include "Core/OS.h"
#include "Core/Engine.h"
#include "Core/Application.h"
#include "Core/Debug/Log.h"


static Engine* engine = nullptr;
static MainLoop* mainLoop = nullptr;

uint32_t Main::frame = 0;


void Main::Setup(int argc, char *argv[])
{
    engine = new Engine();
}

bool Main::Start()
{
    Log::Init();

    // TODO: Make this reference counted!
    mainLoop = new MainLoop();

    OS::GetSingleton()->SetMainLoop(mainLoop);

    GR_CORE_INFO("Main started");

    return true;
}

bool Main::Step()
{
    frame++;

    //Engine::GetSingleton()->Step();

    mainLoop->Step(0);
    Application::GetSingleton()->Step(0);

    return true;
}
