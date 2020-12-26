#include "grpch.h"
#include "MainLoop.h"

#include "Debug/Profiling.h"
#include "Core/Application.h"


bool MainLoop::OnProcess(float DeltaTimeMS)
{
    GR_PROF_FRAME_MARK;

    bool appOk = Application::GetSingleton()->OnProcess(0);

    return appOk;
}
