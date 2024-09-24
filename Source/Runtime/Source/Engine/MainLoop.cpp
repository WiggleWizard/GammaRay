#include "MainLoop.h"

#include "Engine.h"

void MainLoop::Intialize()
{
    
}

void MainLoop::Loop()
{
    while (!GEngine->WantsToQuit())
    {
        GEngine->Process();
    }
}
