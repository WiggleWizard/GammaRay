#include "Engine/Engine.h"
#include "Engine/ModuleManager.h"

DEFINE_LOGGER_STATIC(LogMain, LogVerbosity::Type::Console)

int main(int argc, char** argv)
{
    spdlog::set_pattern("[%H:%M:%S %z] [%n] [%L] %v");

    ModuleManager::Get().InitializeEngineModules();

    GEngine = NewObject<Engine>();
    GEngine->Initialize();
}