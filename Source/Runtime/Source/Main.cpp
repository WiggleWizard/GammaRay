#include "Engine/Engine.h"
#include "Engine/ModuleManager.h"

DEFINE_LOG_CATEGORY_STATIC(LogMain, LogVerbosity::Type::Console)

int main(int argc, char** argv)
{
    ModuleManager::Get().InitializeEngineModules();

    GEngine = MakeShared<Engine>();
    GEngine->Initialize();
}