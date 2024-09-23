#include "ModuleManager.h"

int ModuleManager::RegisterEngineModuleFactoryFunction(const StringName& moduleName, CreateEngineModuleFn& factoryFn)
{
    engineModuleFactories[moduleName] = factoryFn;
    return 0;
}

void ModuleManager::InitializeEngineModules()
{
    for (const auto& [moduleName, moduleFactoryFn] : engineModuleFactories)
    {
        
    }
}
