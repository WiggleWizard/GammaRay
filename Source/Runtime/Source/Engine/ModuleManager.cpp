#include "ModuleManager.h"

#include "Engine/EngineModule.h"

int ModuleManager::RegisterEngineModuleFactoryFunction(const StringName& moduleName, CreateEngineModuleFn& factoryFn)
{
    engineModuleFactories[moduleName] = factoryFn;
    return 0;
}

void ModuleManager::InitializeEngineModules()
{
    for (const auto& [moduleName, moduleFactoryFn] : engineModuleFactories)
    {
        auto engineModuleInstance = moduleFactoryFn();
        engineModules[moduleName] = engineModuleInstance.release();
    }
}
