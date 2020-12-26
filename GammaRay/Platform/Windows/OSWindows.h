#pragma once

#include "Core/OS.h"
#include "Core/Core.h"
#include "Core/Application.h"

#include "Main/Main.h"


class MainLoop;

class GAMMARAY_API OSWindows : public OS
{
    MainLoop* mainLoop = nullptr;
    bool m_forceQuit = false;

public:
    void Run();

    void SetMainLoop(MainLoop* newMainLoop) override;

    OSWindows() {};
    ~OSWindows() {};
};
