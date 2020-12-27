#pragma once

#include "Core/Application.h"
#include "OSWindows.h"


extern Application* CreateApplication();

int main(int argc, char** argv)
{
    Main::Setup(argc, argv);

    OSWindows* os = new OSWindows();
    Application* application = CreateApplication();

    Main::SetApplicationInstance(application);

    Main::Start();
    os->Run();
}
