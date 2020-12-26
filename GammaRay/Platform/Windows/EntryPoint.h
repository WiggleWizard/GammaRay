#pragma once

#include "Core/Application.h"
#include "OSWindows.h"


extern Application* CreateApplication();

int main(int argc, char** argv)
{
    OSWindows* os = new OSWindows();

    Main::Setup(argc, argv);
    Main::SetApplicationInstance(CreateApplication());

    Main::Start();
    os->Run();
}
