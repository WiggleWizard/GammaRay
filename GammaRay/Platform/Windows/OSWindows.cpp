#include "grpch.h"
#include "OSWindows.h"

#include "Core/Application.h"


void OSWindows::Run()
{
    while(!m_forceQuit)
    {
        if(!Main::OnProcess())
            break;
    };
}

void OSWindows::SetMainLoop(MainLoop* newMainLoop)
{
    mainLoop = newMainLoop;
}
