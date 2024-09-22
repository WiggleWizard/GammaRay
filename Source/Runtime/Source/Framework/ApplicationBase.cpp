#include "ApplicationBase.h"

#include "CoreMinimal.h"

#include <SDL.h>

#undef CreateWindow

ApplicationBase* ApplicationBase::instance = nullptr;
ApplicationBase::CreateInstanceFunction ApplicationBase::CreateInstance = nullptr;

DEFINE_LOG_CATEGORY_STATIC(LogApplicationBase, LogVerbosity::Type::Console)

ApplicationBase::ApplicationBase()
{
    instance = this;
}

int ApplicationBase::Main(int arc, char** argv)
{
    // TODO: Parse and/or store command line here

    return Main();
}

int ApplicationBase::Main()
{
    const std::unique_ptr<ApplicationBase> app(CreateInstance());
    app->InitializeApplication();
    return 0;
}

void ApplicationBase::CreateWindow()
{
    SDL_CreateWindow("Hello World", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
}

void ApplicationBase::InitializeApplication()
{
    Logging::BasicLog(LogApplicationBase, "Hello WOrld {}", 11);

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        
    }

    OnInitialized();
}
