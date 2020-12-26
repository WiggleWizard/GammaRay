#pragma once

#include "Core/Application.h"
#include "OSWindows.h"


extern Application* CreateApplication();

int main(int argc, char** argv)
{
    OSWindows os;

    Application* app = CreateApplication();

    Main::Start();
    os.Run();
}
